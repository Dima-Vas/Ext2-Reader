

#ifndef INFO_PRINT_H
#define INFO_PRINT_H
#include <stdio.h>
#include <time.h>
#include "SuperBlock.h"
#include "BlockDescriptor.h"
#include "Directory.h"
#include "main.h"
#include <asm-generic/int-ll64.h>

void SuperBlockPrint(struct SuperBlock* superblock) {
    printf("Inodes count: %u\n", superblock->s_inodes_count);
    printf("Blocks count: %u\n", superblock->s_blocks_count);
    printf("Reserved blocks count: %u\n", superblock->s_r_blocks_count);
    printf("Free blocks count: %u\n", superblock->s_free_blocks_count);
    printf("Free inodes count: %u\n", superblock->s_free_inodes_count);
    printf("First Data Block: %u\n", superblock->s_first_data_block);
    printf("Block size: %u\n", 1024 << superblock->s_log_block_size);
    printf("Fragment size: %d\n", 1024 << superblock->s_log_frag_size);
    printf("Blocks per group: %u\n", superblock->s_blocks_per_group);
    printf("Fragments per group: %u\n", superblock->s_frags_per_group);
    printf("Inodes per group: %u\n", superblock->s_inodes_per_group);
    printf("Last mount time: %u\n", superblock->s_mtime);
    printf("Last write time: %u\n", superblock->s_wtime);
    printf("Mount count since last check: %u\n", superblock->s_mnt_count);
    printf("Maximal mount count before a check: %d\n", superblock->s_max_mnt_count);
    printf("Magic signature: 0x%04X\n", superblock->s_magic);
    printf("File system state: %u\n", superblock->s_state);
    printf("Behavior when detecting errors: %u\n", superblock->s_errors);
    printf("Minor revision level: %u\n", superblock->s_minor_rev_level);
    printf("Time of last check: %u\n", superblock->s_lastcheck);
    printf("Max. time between checks: %u\n", superblock->s_checkinterval);
    printf("Creator OS ID: %u\n", superblock->s_creator_os);
    printf("Major revision level: %u\n", superblock->s_rev_level);
    printf("User ID that can use reserved blocks: %u\n", superblock->s_def_resuid);
    printf("Group ID that can use reserved blocks: %u\n", superblock->s_def_resgid);
    printf("First non-reserved inode: %u\n", superblock->s_first_ino);
    printf("Size of inode structure: %u\n", superblock->s_inode_size);
    printf("Block group this superblock is part of: %u\n", superblock->s_block_group_nr);
    printf("Optional features present: %u\n", superblock->s_feature_compat);
    printf("Readonly-compatible feature set: %u\n", superblock->s_feature_ro_compat);
    printf("UUID for volume: ");
    for (int i = 0; i < 16; ++i) {
        printf("%02X ", superblock->s_uuid[i]);
    }
    printf("\n");
    printf("Volume name: %s\n", superblock->s_volume_name);
    printf("Directory where last mounted: %s\n", superblock->s_last_mounted);
    printf("Algorithm usage bitmap: %u\n", superblock->s_algorithm_usage_bitmap);
    printf("Nr of blocks to try to preallocate: %u\n", superblock->s_prealloc_blocks);
    printf("Nr to preallocate for dirs: %u\n", superblock->s_prealloc_dir_blocks);
}

void BlockDescriptorPrint(struct BlockDescriptor* blockdescriptor) {
    printf("Blocks bitmap block: %u\n", blockdescriptor->bg_block_bitmap);
    printf("Inodes bitmap block: %u\n", blockdescriptor->bg_inode_bitmap);
    printf("Inodes table block: %u\n", blockdescriptor->bg_inode_table);
    printf("Free blocks count: %u\n", blockdescriptor->bg_free_blocks_count);
    printf("Free inodes count: %u\n", blockdescriptor->bg_free_inodes_count);
    printf("Used directories count: %u\n", blockdescriptor->bg_used_dirs_count);
    printf("Padding: %u\n", blockdescriptor->bg_pad);
}

void printDirectory(struct Directory* dir, char* path) {
    struct Inode* inode = malloc(sizeof(struct Inode));

    long offset = SIZE_BLOCK * BLOCKDESCRIPTOR->bg_inode_table + SIZE_INODE * (dir->inode - 1);
    if (fseek(image, offset, SEEK_SET) != 0) {
        perror("Error while looking for inode block");
        exit(EXIT_FAILURE);
    }
    if (fread(inode, 1, SIZE_STRUCT_INODE, image) != SIZE_STRUCT_INODE) {
        perror("Incorrect size of inode read");
        exit(EXIT_FAILURE);
    }

    __u64 file_size = ((__u64)inode->i_size_hi << 32) | inode->i_size_lo;
    time_t creation_time = inode->i_ctime;
    time_t last_access_time = inode->i_atime;
    
    printf("%s/%s", path, dir->name);
    if (verbose) {
        int i = strlen(dir->name) + strlen(path);
        while (i < 80) {
            printf(" ");
            i++;
        }
        dir->file_type == 2 ? printf("*  ") : printf("f  ");
        printf("  %u  ", dir->inode);
        printf("  %o  ", inode->i_mode);
        printf("  %llu  ", file_size);
        printf("  %d  ", inode->i_links_count);
        printf("  %d  ", inode->i_flags);
        printf("  %d  ", inode->i_block[0]);
        printf("  %s  ", ctime(&creation_time));
        printf("  %s  \n", ctime(&last_access_time));
    } else {
        printf("\n");
    }
    
    free(inode);
}

#endif
