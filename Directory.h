

#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <asm-generic/int-ll64.h>
#include <dirent.h>

#pragma pack(push, 1)
struct Directory {
    __u32 inode;      // Inode number
    __u16 rec_len;    // Directory entry length
    __u8  name_len;   // Name length
    __u8  file_type;  // File type
    char  name[255];   // File name
};
#pragma(pop)
#endif
