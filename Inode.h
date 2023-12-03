
#ifndef INODE_H
#define INODE_H
#include <asm-generic/int-ll64.h>

#pragma pack(push, 1)
struct Inode {
    __u16 i_mode;            // Type and access rights
    __u16 i_uid;             // User ID
    __u32 i_size_lo;         // Low 32 bits of size
    __u32 i_atime;           // Last Access Time (in POSIX time)
    __u32 i_ctime;           // Creation Time
    __u32 i_mtime;           // Last Modification time
    __u32 i_dtime;           // Deletion time
    __u16 i_gid;             // Group ID
    __u16 i_links_count;     // Amount of hard links
    __u32 i_blocks;          // Amount of 512-byte sectors in file
    __u32 i_flags;           // Flags
    __u32 i_osd1;            // OS Specific value 1, for Linux - reserved
    __u32 i_block[12];       // Direct Block Pointers 0-11
    __u32 i_singly_block;    // Singly Indirect Block Pointer
    __u32 i_doubly_block;    // Doubly Indirect Block Pointer
    __u32 i_triply_block;    // Triply Indirect Block Pointer
    __u32 i_generation;      // Generation - file version for NFS
    __u32 i_file_acl;        // Block containing ACL
    __u32 i_size_hi;         // High 32 bits of size
};
#pragma pack(pop)

#endif