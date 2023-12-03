

#ifndef MAIN_H
#define MAIN_H

#include "SuperBlock.h"
#include "BlockDescriptor.h"
#include "Inode.h"
#include "Directory.h"
#include <stdio.h>

size_t SIZE_SUPERBLOCK      = sizeof(struct SuperBlock);
size_t SIZE_BLOCKDESCRIPTOR = sizeof(struct BlockDescriptor);
size_t SIZE_STRUCT_INODE    = sizeof(struct Inode);
size_t SIZE_DIRECTORY       = sizeof(struct Directory);

size_t SIZE_BLOCK;
size_t SIZE_INODE;
char* BLOCK;

struct SuperBlock*      SUPERBLOCK;
struct BlockDescriptor* BLOCKDESCRIPTOR;

FILE* image;

int verbose;

#endif