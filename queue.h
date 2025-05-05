#ifndef QUEUE_H
#define QUEUE_H

#include "task.h"

typedef struct QueueNode {
    Task task;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} TaskQueue;

typedef struct StackNode {
    Task task;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
    int size;
} UndoStack;

// Function prototypes
void enqueue(Task task);
Task dequeue();
void displayQueue();
void freeQueue(TaskQueue *queue);
void pushUndo(Task task);
Task popUndo();
void freeStack();

#endif