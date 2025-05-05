// ======== tree.h ========
#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include "robot.h"

/**
 * Generic n-ary tree node representing factory zones or departments
 * - zoneName: label for this node
 * - children: dynamic array of child pointers
 * - childCount: number of children
 */
typedef struct TreeNode {
    char zoneName[50];
    struct TreeNode **children;
    int childCount;
} TreeNode;

/**
 * Binary Search Tree node for robots, keyed by Robot.id
 */
typedef struct BSTNode {
    Robot robot;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

// -----------------------------------------------------------------------------
// Factory structure (n-ary tree) functions
// -----------------------------------------------------------------------------

/**
 * Create an empty factory tree root (e.g., "Factory Root").
 * @return Pointer to new TreeNode
 */
TreeNode *createFactoryTree(void);

/**
 * Create a standalone tree node with given zone name.
 * @param name  Null-terminated string (max 49 chars)
 * @return Pointer to new TreeNode
 */
TreeNode *createNode(const char *name);

/**
 * Add a child node to a parent in the n-ary tree.
 * @param parent  Pointer to parent TreeNode
 * @param child   Pointer to child TreeNode to attach
 */
void addChild(TreeNode *parent, TreeNode *child);

/**
 * Recursively display the factory tree structure with indentation.
 * @param node   Current TreeNode to display
 * @param depth  Indentation depth (0 for root)
 */
void displayFactoryTree(const TreeNode *node, int depth);

/**
 * Recursively free all nodes in the factory tree.
 * @param node  Root of subtree to free
 */
void freeFactoryTree(TreeNode *node);

// -----------------------------------------------------------------------------
// Robot Binary Search Tree (BST) functions
// -----------------------------------------------------------------------------

/**
 * Insert a robot into the BST, or update existing node if ID matches.
 * @param root   Current BST root (may be NULL)
 * @param robot  Robot data to insert
 * @return New root of the BST
 */
BSTNode *insertRobotBST(BSTNode *root, Robot robot);

/**
 * Search for a robot by ID in the BST.
 * @param root  BST root
 * @param id    Robot ID to find
 * @return Pointer to BSTNode if found, NULL otherwise
 */
BSTNode *searchRobotBST(BSTNode *root, int id);

/**
 * Inorder traversal of BST, printing robot details in ID order.
 * @param root  BST root
 */
void inorderTraversalBST(const BSTNode *root);

/**
 * Recursively free all nodes in the robot BST.
 * @param root  BST root to free
 */
void freeRobotBST(BSTNode *root);

#endif // TREE_H