#ifndef TREE_H
#define TREE_H

#include "robot.h"

typedef struct TreeNode {
    char zoneName[50];
    struct TreeNode** children;
    int childCount;
} TreeNode;

typedef struct BSTNode {
    Robot robot;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Factory Tree functions
TreeNode* createFactoryTree();
TreeNode* createNode(const char* name);
void addChild(TreeNode* parent, TreeNode* child);
void displayFactoryTree(TreeNode* node, int depth);
void freeFactoryTree(TreeNode* node);

// Robot BST functions
BSTNode* insertRobotBST(BSTNode* root, Robot robot);
BSTNode* searchRobotBST(BSTNode* root, int id);
void inorderTraversalBST(BSTNode* root);
void freeRobotBST(BSTNode* root);

#endif