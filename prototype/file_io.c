#include "file_io.h"
#include "robot.h"
#include "task.h"
#include "queue.h"
#include "tree.h"
#include "production.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern TaskQueue assemblyQueue;
extern UndoStack undoStack;
extern Robot robots[MAX_ROBOTS];
extern Task tasks[MAX_TASKS];
extern int robotCount;
extern int taskCount;

// Helper prototypes
static void saveQueue(FILE *file);
static void loadQueue(FILE *file);
static void saveStack(FILE *file);
static void loadStack(FILE *file);
static void saveFactoryTree(FILE *file, TreeNode *node);
static TreeNode *loadFactoryTree(FILE *file);

int saveSession(const char *filename, TreeNode *factoryTree) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error: Could not create save file '%s'!\n", filename);
        return -1;
    }

    // Save core data
    fwrite(&robotCount, sizeof(robotCount), 1, file);
    fwrite(robots, sizeof(Robot), robotCount, file);

    fwrite(&taskCount, sizeof(taskCount), 1, file);
    fwrite(tasks, sizeof(Task), taskCount, file);

    // Save queue/stack
    saveQueue(file);
    saveStack(file);

    // Save factory tree
    saveFactoryTree(file, factoryTree);

    fclose(file);
    return 0;
}

TreeNode *loadSession(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error: Could not open session file '%s'!\n", filename);
        return NULL;
    }

    // Clear current state
    freeQueue(&assemblyQueue);
    freeStack(&undoStack);
    robotCount = taskCount = 0;

    // Load robots
    fread(&robotCount, sizeof(robotCount), 1, file);
    fread(robots, sizeof(Robot), robotCount, file);

    // Load tasks
    fread(&taskCount, sizeof(taskCount), 1, file);
    fread(tasks, sizeof(Task), taskCount, file);

    // Load queue/stack
    loadQueue(file);
    loadStack(file);

    // Load factory tree
    TreeNode *factoryTree = loadFactoryTree(file);

    fclose(file);
    return factoryTree;
}

static void saveQueue(FILE *file) {
    int size = assemblyQueue.size;
    fwrite(&size, sizeof(size), 1, file);
    QueueNode *curr = assemblyQueue.front;
    while (curr) {
        fwrite(&curr->task, sizeof(Task), 1, file);
        curr = curr->next;
    }
}

static void loadQueue(FILE *file) {
    int size;
    fread(&size, sizeof(size), 1, file);
    for (int i = 0; i < size; ++i) {
        Task t;
        fread(&t, sizeof(Task), 1, file);
        enqueue(t);
    }
}

static void saveStack(FILE *file) {
    int size = undoStack.size;
    fwrite(&size, sizeof(size), 1, file);
    StackNode *curr = undoStack.top;
    while (curr) {
        fwrite(&curr->task, sizeof(Task), 1, file);
        curr = curr->next;
    }
}

static void loadStack(FILE *file) {
    int size;
    fread(&size, sizeof(size), 1, file);
    for (int i = 0; i < size; ++i) {
        Task t;
        fread(&t, sizeof(Task), 1, file);
        pushUndo(t);
    }
}

static void saveFactoryTree(FILE *file, TreeNode *node) {
    if (!node) {
        int marker = 0;
        fwrite(&marker, sizeof(marker), 1, file);
        return;
    }
    int marker = 1;
    fwrite(&marker, sizeof(marker), 1, file);
    // TODO: Serialize node data fields here (e.g., node->id, node->name)
    fwrite(&node->id, sizeof(node->id), 1, file);
    int nameLen = strlen(node->name) + 1;
    fwrite(&nameLen, sizeof(nameLen), 1, file);
    fwrite(node->name, sizeof(char), nameLen, file);

    // Write number of children
    fwrite(&node->childCount, sizeof(node->childCount), 1, file);
    for (int i = 0; i < node->childCount; ++i) {
        saveFactoryTree(file, node->children[i]);
    }
}

static TreeNode *loadFactoryTree(FILE *file) {
    int marker;
    fread(&marker, sizeof(marker), 1, file);
    if (!marker) return NULL;

    TreeNode *node = malloc(sizeof(TreeNode));
    fread(&node->id, sizeof(node->id), 1, file);
    int nameLen;
    fread(&nameLen, sizeof(nameLen), 1, file);
    node->name = malloc(nameLen);
    fread(node->name, sizeof(char), nameLen, file);

    fread(&node->childCount, sizeof(node->childCount), 1, file);
    node->children = malloc(sizeof(TreeNode*) * node->childCount);
    for (int i = 0; i < node->childCount; ++i) {
        node->children[i] = loadFactoryTree(file);
    }
    return node;
}
