#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <asm-generic/int-ll64.h>
#include "SuperBlock.h"
#include "InfoPrint.h"
#include "BlockDescriptor.h"
#include "Inode.h"
#include "Directory.h"
#include "main.h"

#define ROOT_INODE 2
#define FILE_ENTRY 1
#define DIR_ENTRY 2
#define DIRECT_BLOCKS 11

// reads directory entry from the block from current offset
int read_dirent(struct Directory* dir, char* img, size_t* curr_offset) {
    memset(dir->name, '\0', sizeof(dir->name));
    if (!memcpy(&(dir->inode), img + *curr_offset, sizeof(struct Directory) - sizeof(dir->name))) {
        return -1;
    } else {
        *curr_offset +=sizeof(struct Directory) - sizeof(dir->name);
    }
    if (!memcpy(dir->name, img + *curr_offset, dir->name_len)) {
        return -1;
    }
    else {
        *curr_offset+=dir->name_len;
    }
    *curr_offset += (4 - *curr_offset % 4) % 4; // because %4 alignment
    return 0;
}

void recurse(struct Inode* inode, char* datablock, char* curr_path) {
    size_t curr_dir_block_offset = 0;
    __u32 subdir_amount = 0;
    int* subdir_inodes;
    struct Directory* dir = malloc(SIZE_DIRECTORY);

    // read once - print the content and count dir inodes
    do {
        if (read_dirent(dir, datablock, &curr_dir_block_offset)) {
            perror("Bad read");
            exit(EXIT_FAILURE);
        } else {
            if (dir->file_type == DIR_ENTRY) {
                subdir_amount++;
            }
            if (dir->inode && !(dir->name[0] == '.' && (dir->name[1] == '\0' || dir->name[1] == '.'))) {
                printDirectory(dir, curr_path);
            }   
        }
    } while (dir->inode != 0);

    // initialize the dir inodes
    curr_dir_block_offset = 0;
    subdir_inodes = (__u32*)malloc(subdir_amount * sizeof(__u32));
    char** subdir_paths = malloc(subdir_amount * sizeof(char*));
    size_t curr_subdir_ptr = 0;
    size_t curr_subdir_path_ptr = 0;
    char* name_to_record;
    do {
        if (read_dirent(dir, datablock, &curr_dir_block_offset)) {
            perror("Bad root read");
            exit(EXIT_FAILURE);
        } else if (!dir->name_len) { // end of entries
            break;
        } else if (!dir->inode || (dir->name[0] == '.' && (dir->name[1] == '\0' || dir->name[1] == '.')) || dir->file_type != DIR_ENTRY) { 
            continue;
        } else {
            subdir_inodes[curr_subdir_ptr++] = dir->inode;
            name_to_record = malloc(dir->name_len + 1);
            memcpy(name_to_record, dir->name, dir->name_len);
            subdir_paths[curr_subdir_path_ptr++] = name_to_record;
        }
    } while (dir->inode != 0);

    char* new_curr_path = malloc(sizeof(dir->name));

    for (size_t i = 0; i < curr_subdir_ptr; i++) {
        sprintf(new_curr_path, "%s/%s", curr_path, subdir_paths[i]);
        long offset = SIZE_BLOCK * BLOCKDESCRIPTOR->bg_inode_table + SIZE_INODE * (subdir_inodes[i] - 1);
        if (fseek(image, offset, SEEK_SET) != 0) {
            perror("Error while looking for inode block");
            exit(EXIT_FAILURE);
        }
        if (fread(inode, 1, SIZE_STRUCT_INODE, image) != SIZE_STRUCT_INODE) {
            perror("Incorrect size of inode read");
            exit(EXIT_FAILURE);
        }
        for (size_t j = 0; j < DIRECT_BLOCKS; ++j) {
            if (inode->i_block[j] != 0) {
                if (fseek(image, SIZE_BLOCK * inode->i_block[j], SEEK_SET) != 0) {
                    perror("Error while looking for root node");
                    exit(EXIT_FAILURE);
                }
                if (fread(datablock, 1, SIZE_BLOCK, image) != SIZE_BLOCK) {
                    perror("Bad block read");
                    exit(EXIT_FAILURE);
                }
                recurse(inode, datablock, new_curr_path);
            }
        }
    }
    free(dir);
    free(subdir_inodes);
    free(new_curr_path);
    for (__u32 i = 0; i < curr_subdir_path_ptr; i++) {
        free(subdir_paths[i]);
    }
    free(subdir_paths);
}

// BGDT is on 0x1000
// root data is on 0xA5000
int main(int argc, char* argv[]) {
    char* image_path = argv[1];
    verbose = argc > 2 && !strcmp("-v", argv[2]);

    SUPERBLOCK      = malloc(SIZE_SUPERBLOCK);
    BLOCKDESCRIPTOR = malloc(SIZE_BLOCKDESCRIPTOR);

    struct Inode*       INODE       = malloc(SIZE_STRUCT_INODE);
    struct Directory*   DIRECTORY   = malloc(SIZE_DIRECTORY);

    printf("\n\033[1;32m%s\033[0m\n\n", image_path);

    image = fopen(image_path, "rb");
    if (image == NULL) {
        perror("Bad address");
        exit(EXIT_FAILURE);
    }

    // finds the superblock
    if (fseek(image, 1024, SEEK_SET) != 0) {
        perror("Error while looking for superblock");
        exit(EXIT_FAILURE);
    }

    // reads the superblock
    if (fread(SUPERBLOCK, 1, SIZE_SUPERBLOCK, image) != SIZE_SUPERBLOCK) {
        perror("Incorrect size of superblock read");
        exit(EXIT_FAILURE);
    }

    // checks the magic
    if (SUPERBLOCK->s_magic != 0xEF53) {
        perror("Bad magic");
        exit(EXIT_FAILURE);
    }

    // calculates sizes of block and inode
    SIZE_BLOCK = (1024 << SUPERBLOCK->s_log_block_size);
    SIZE_INODE = SUPERBLOCK->s_inode_size;
    BLOCK = malloc(SIZE_BLOCK);

    // finds the BGDT
    if (fseek(image, SIZE_BLOCK, SEEK_SET) != 0) {
        perror("Error while looking for blockdescriptor");
        exit(EXIT_FAILURE);
    }

    // reads the BGDT
    if (fread(BLOCKDESCRIPTOR, 1, SIZE_BLOCKDESCRIPTOR, image) != SIZE_BLOCKDESCRIPTOR) {
        perror("Incorrect size of blockdescriptor read");
        exit(EXIT_FAILURE);
    }

    // prints basic info
    SuperBlockPrint(SUPERBLOCK);
    printf("\n");
    BlockDescriptorPrint(BLOCKDESCRIPTOR);

    // finds root inode
    long root_offset = SIZE_BLOCK * BLOCKDESCRIPTOR->bg_inode_table + SIZE_INODE * (ROOT_INODE - 1);
    if (fseek(image, root_offset, SEEK_SET) != 0) {
        perror("Error while looking for inode block");
        exit(EXIT_FAILURE);
    }

    // reads the root inode
    if (fread(INODE, 1, SIZE_STRUCT_INODE, image) != SIZE_STRUCT_INODE) {
        perror("Incorrect size of inode read");
        exit(EXIT_FAILURE);
    }

    // finds root dir data block
    if (fseek(image, SIZE_BLOCK * INODE->i_block[0], SEEK_SET) != 0) {
        perror("Error while looking for root node");
        exit(EXIT_FAILURE);
    }

    // reads root dir data block
    if (fread(BLOCK, 1, SIZE_BLOCK, image) != SIZE_BLOCK) {
        perror("Bad root block read");
        exit(EXIT_FAILURE);
    }

    printf("\nNAME                                                      TYPE   INODE   MODE   SIZE   LINKS   FLAGS   FIRSTBLOCK   CREATEDAT   ACCESSEDAT\n");
    recurse(INODE, BLOCK, "");
    printf("\nNAME                                                      TYPE   INODE   MODE   SIZE   LINKS   FLAGS   FIRSTBLOCK   CREATEDAT   ACCESSEDAT\n");

    free(SUPERBLOCK);
    free(BLOCKDESCRIPTOR);
    free(INODE);
    free(DIRECTORY);
    free(BLOCK);
    fclose(image);
    return 0;
}