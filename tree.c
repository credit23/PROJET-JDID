#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------ factory tree n array

TreeNode* createFactoryTree() {
    TreeNode* factory = createNode("Factory");
    TreeNode* rawMaterials = createNode("Raw Materials Zone");
    TreeNode* assembly = createNode("Assembly Zone");
    TreeNode* qualityControl = createNode("Quality Control");
    TreeNode* dispatch = createNode("Dispatch Section");
    TreeNode* robotArmA = createNode("Robot Arm A");
    TreeNode* robotArmB = createNode("Robot Arm B");
    addChild(assembly, robotArmA);
    addChild(assembly, robotArmB);
    addChild(factory, rawMaterials);
    addChild(factory, assembly);
    addChild(factory, qualityControl);
    addChild(factory, dispatch);
    
    return factory;
}

TreeNode* createNode(const char* name) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    strncpy(node->zoneName, name, 49);
    node->zoneName[49] = '\0';
    node->children = NULL;
    node->childCount = 0;
    return node;
}

void addChild(TreeNode* parent, TreeNode* child) {
    parent->children = realloc(parent->children, 
                              (parent->childCount + 1) * sizeof(TreeNode*));
    parent->children[parent->childCount++] = child;
}

void displayFactoryTree(TreeNode* node, int depth) {
    if(!node) return;
    for(int i = 0; i < depth; i++) printf("--");
    printf("|%s\n", node->zoneName);
    for(int i = 0; i < node->childCount; i++) {
        displayFactoryTree(node->children[i], depth + 1);
    }
}

void freeFactoryTree(TreeNode* node) {
    if(!node) return;
    for(int i = 0; i < node->childCount; i++) {
        freeFactoryTree(node->children[i]);
    }
    
    free(node->children);
    free(node);
}

// -------- robot bst

BSTNode* insertRobotBST(BSTNode* root, Robot robot) {
    if(!root) {
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->robot = robot;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if(robot.id < root->robot.id) {
        root->left = insertRobotBST(root->left, robot);
    } else {
        root->right = insertRobotBST(root->right, robot);
    }
    return root;
}

BSTNode* searchRobotBST(BSTNode* root, int id) {
    if(!root) return NULL;
    
    if(id == root->robot.id) {
        return root;
    } else if(id < root->robot.id) {
        return searchRobotBST(root->left, id);
    } else {
        return searchRobotBST(root->right, id);
    }
}

void inorderTraversalBST(BSTNode* root) {
    if(!root) return;
    
    inorderTraversalBST(root->left);
    printf("Robot ID: %-5d | Name: %-20s | Status: %d\n",
          root->robot.id, root->robot.name, root->robot.status);
    inorderTraversalBST(root->right);
}

void freeRobotBST(BSTNode* root) {
    if(!root) return;
    
    freeRobotBST(root->left);
    freeRobotBST(root->right);
    free(root);
}