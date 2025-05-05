#ifndef FILE_IO_H
#define FILE_IO_H

#include "tree.h"

int saveSession(const char *filename, TreeNode *factoryTree);
TreeNode *loadSession(const char *filename);

#endif
