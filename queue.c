#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "task.h"

TaskQueue assemblyQueue = {NULL, NULL, 0};
UndoStack undoStack = {NULL, 0};

//--------------queue
void enqueue(Task task) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if(!newNode) {
        printf("\033[31mError: Memory allocation failed!\033[0m\n");
        return;
    }
    newNode->task = task;
    newNode->next = NULL;
    if(assemblyQueue.rear == NULL) {
        assemblyQueue.front = assemblyQueue.rear = newNode;
    } else {
        assemblyQueue.rear->next = newNode;
        assemblyQueue.rear = newNode;
    }
    assemblyQueue.size++;
    printf("\033[32mTask %d queued successfully!\033[0m\n", task.id);
}

Task dequeue() {
    Task emptyTask = {.id = -1};
    if(assemblyQueue.front == NULL) {
        printf("\033[31mQueue is empty!\033[0m\n");
        return emptyTask;
    }
    QueueNode* temp = assemblyQueue.front;
    Task dequeuedTask = temp->task;
    
    assemblyQueue.front = assemblyQueue.front->next;
    if(assemblyQueue.front == NULL) {
        assemblyQueue.rear = NULL;
    }
    free(temp);
    assemblyQueue.size--;
    pushUndo(dequeuedTask);
    return dequeuedTask;
}

void displayQueue() {
    if(assemblyQueue.front == NULL) {
        printf("\n\033[33mTask Queue is empty!\033[0m\n");
        return;
    }
    QueueNode* current = assemblyQueue.front;
    printf("\n\033[36m=== Task Queue (%d tasks) ===\033[0m\n", assemblyQueue.size);
    int position = 1;
    while(current != NULL) {
        printf("\n\033[33mPosition %d:\033[0m\n", position++);
        printTaskDetails(current->task);
        current = current->next;
    }
    printf("\033[36m==============================\033[0m\n");
}

void freeQueue(TaskQueue *queue) {
    QueueNode* current = queue->front;
    while(current != NULL) {
        QueueNode* next = current->next;
        free(current);
        current = next;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    printf("\033[32mQueue memory freed!\033[0m\n");
}
//---------------stack

void pushUndo(Task task) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if(!newNode) {
        printf("\033[31mError: Memory allocation failed!\033[0m\n");
        return;
    }
    newNode->task = task;
    newNode->next = undoStack.top;
    undoStack.top = newNode;
    undoStack.size++;
}
Task popUndo() {
    Task emptyTask = {.id = -1};
    
    if(undoStack.top == NULL) {
        printf("\033[31mUndo stack is empty!\033[0m\n");
        return emptyTask;
    }
    StackNode* temp = undoStack.top;
    Task poppedTask = temp->task;
    
    undoStack.top = undoStack.top->next;
    free(temp);
    undoStack.size--;
    return poppedTask;
}

void freeStack() {
    StackNode* current = undoStack.top;
    while(current != NULL) {
        StackNode* next = current->next;
        free(current);
        current = next;
    }
    undoStack.top = NULL;
    undoStack.size = 0;
    printf("\033[32mUndo stack memory freed!\033[0m\n");
}