// ======== queue.h ========
#ifndef QUEUE_H
#define QUEUE_H

#include "task.h"

/**
 * Task queue for FIFO scheduling
 */
typedef struct QueueNode {
    Task task;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
    int size;
} TaskQueue;

/**
 * Undo stack for LIFO task rollback
 */
typedef struct StackNode {
    Task task;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
    int size;
} UndoStack;

// Global instances
extern TaskQueue assemblyQueue;
extern UndoStack undoStack;

// Queue operations
/** Enqueue a task to the assembly queue */
void enqueue(Task task);
/** Dequeue the next task; returns Task with id==-1 if empty */
Task dequeue(void);
/** Display all tasks currently in the queue */
void displayQueue(void);
/** Free all nodes in the given queue and reset it */

// Undo stack operations
/** Push a task onto the undo stack */
void pushUndo(Task task);
/** Pop the most recent task; returns Task with id==-1 if empty */
Task popUndo(void);
/** Free all nodes in the given undo stack and reset it */
void freeStack(UndoStack *stack);

void freeQueue(TaskQueue *queue);
void freeStack(UndoStack *stack);


#endif // QUEUE_H