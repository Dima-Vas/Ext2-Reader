
#ifndef BLOCK_DESCRIPTOR_H
#define BLOCK_DESCRIPTOR_H
#include <asm-generic/int-ll64.h>

#pragma pack(push, 1)
struct BlockDescriptor {
    __u32 bg_block_bitmap; /* 0x00: Blocks bitmap block */
    __u32 bg_inode_bitmap; /* 0x04: Inodes bitmap block */
    __u32 bg_inode_table; /* 0x08: Inodes table block */
    __u16 bg_free_blocks_count;/* 0x0C: Free blocks count */
    __u16 bg_free_inodes_count;/* 0x0E: Free inodes count */
    __u16 bg_used_dirs_count; /* 0x10: Directories count */
    __u16 bg_pad;
    __u32 bg_reserved[3];
};
#pragma pack(pop)

#endif