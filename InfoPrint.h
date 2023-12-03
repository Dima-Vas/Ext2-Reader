

#ifndef INFO_PRINT_H
#define INFO_PRINT_H
#include <stdio.h>
#include "SuperBlock.h"
#include "BlockDescriptor.h"
#include "Directory.h"

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

    printf("%s/%s", path, dir->name);
    int i = strlen(dir->name) + strlen(path);
    if (i > 100) {
        printf("h");
    }
    while(i < 100) {
        printf(" ");
        i++;
    }
    dir->file_type == 2 ? printf("*  ") : printf("f  ");
    printf("    %u  \n", dir->inode);

}

#endif
