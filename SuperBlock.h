
#ifndef SUPER_BLOCK_H
#define SUPER_BLOCK_H
#include <asm-generic/int-ll64.h>

#pragma pack(push, 1)
struct SuperBlock {
    __u32 s_inodes_count; /* 0x00: Inodes count */
    __u32 s_blocks_count; /* 0x04: Blocks count */
    __u32 s_r_blocks_count; /* 0x08: Reserved blocks count */
    __u32 s_free_blocks_count;/* 0x0C: Free blocks count */
    __u32 s_free_inodes_count;/* 0x10: Free inodes count */
    __u32 s_first_data_block; /* 0x14: First Data Block */
    __u32 s_log_block_size; /* 0x18: Block size: log2 (block size ) = 10 */
    __s32 s_log_frag_size; /* 0x1C: Fragment size (same log2 as above) */
    __u32 s_blocks_per_group; /* 0x20: Blocks per group */
    __u32 s_frags_per_group; /* 0x24: Fragments per group */
    __u32 s_inodes_per_group; /* 0x28: Inodes per group */
    __u32 s_mtime; /* 0x2C: Last mount time, in POSIX time */
    __u32 s_wtime; /* 0x30: Last write time, in POSIX time */
    __u16 s_mnt_count; /* 0x34: Mount count since last check*/
    __s16 s_max_mnt_count; /* 0x36: Maximal mount count before a check*/
    __u16 s_magic; /* 0x38: Magic signature : 0xEF53 on disk, (0x53 0xEF LE)*/
    __u16 s_state; /* 0x3A: File system state : 1 == FS OK, 2 == FS has errors */
    __u16 s_errors; /* 0x3C: Behaviour when detecting errors :
    1 == ignore, 2 == remount read=only, 3 == kernel panic */
    __u16 s_minor_rev_level; /* 0x3E: minor revision (version ) level */
    __u32 s_lastcheck; /* 0x40: time of last check, in POSIX time */
    __u32 s_checkinterval; /* 0x44: max. time between checks, in POSIX time */
    __u32 s_creator_os; /* 0x48: creator OS ID: eg. 0 == Linux, 3 == FreeBSD */
    __u32 s_rev_level; /* 0x4C: Major revision ( version ) level : 0 == original ,
    1 == v2 format w/ dynamic inode sizes */
    __u16 s_def_resuid; /* 0x50: User ID that can use reserved blocks */
    __u16 s_def_resgid; /* 0x52: Group ID that can use reserved blocks */
    // Below: fields for EXT2_DYNAMIC_REV (V2) superblocks only.
    __u32 s_first_ino; /* 0x54: First non=reserved inode, ver < 1.0: fixed as 11 */
    __u16 s_inode_size; /* 0x58: size of inode structure , ver < 1.0: fixed as 128 */
    __u16 s_block_group_nr; /* 0x5A: Block group this superblock is part of ( if backup copy) */
    __u32 s_feature_compat; /* 0x5C: Optional features present (not required to read or write ,
    mostly == performance=related), for example:
    0x01: preallocate some blocks for new directory
    (see byte 0xCD in superblock)
    0x04: FS has journal == is an ext3 FS
    0x08: inodes have extended attributes
    0x20: Directories use hash index
    Many other: https ://ext4 . wiki . kernel . org/index .php/Ext4_Disk_Layout * __u32 s_feature_incompat; /* 0x60: Incompatible feature set:
    0x01: Compression. Not implemented.
    0x02: Directory entries record the file type
    Many other. */
    __u32 s_feature_ro_compat;/* 0x64: Readonly=compatible feature set:
    0x01: Sparse superblocks == copies of the superblock and
    group descriptors are kept only in the groups whose
    group number is either 0 or a power of 3, 5, or 7.
    0x02: File system uses a 64=bit file size
    0x04: RO_COMPAT_BTREE_DIR, not used
    Many other. */
    __u8 s_uuid[16]; /* 0x68: 128=bit uuid for volume */
    char s_volume_name[16]; /* 0x78: volume name */
    char s_last_mounted[64]; /* 0x88: directory where last mounted */
    __u32 s_algorithm_usage_bitmap; /* 0xC8: For compression, not used */
    __u8 s_prealloc_blocks; /* 0xCC: Nr of blocks to try to preallocate */
    __u8 s_prealloc_dir_blocks;/* 0xCD: Nr to preallocate for dirs */
    __u16 s_padding1;
    __u32 s_reserved[205]; /* Padding to the end of the block */
};
#pragma pack(pop)
#endif