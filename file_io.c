#include "file_io.h"
#include "robot.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

#define SAVE_FILE "factory_state.bin"

static void saveQueue(FILE* file);
static void loadQueue(FILE* file);
static void saveStack(FILE* file);
static void loadStack(FILE* file);

void saveSession() {
    FILE* file = fopen(SAVE_FILE, "wb");
    if(!file) {
        printf("\033[31mError: Could not create save file!\033[0m\n");
        return;
    }
    fwrite(&robotCount, sizeof(int), 1, file);
    fwrite(robots, sizeof(Robot), robotCount, file);
    
    fwrite(&taskCount, sizeof(int), 1, file);
    fwrite(tasks, sizeof(Task), taskCount, file);
    saveQueue(file);
    saveStack(file);

    fclose(file);
    printf("\033[32mSession saved successfully!\033[0m\n");
}

void loadSession() {
    FILE* file = fopen(SAVE_FILE, "rb");
    if(!file) {
        printf("\033[31mError: No saved session found!\033[0m\n");
        return;
    }
    freeQueue(&assemblyQueue);
    freeStack(&undoStack);
    robotCount = taskCount = 0;

    fread(&robotCount, sizeof(int), 1, file);
    fread(robots, sizeof(Robot), robotCount, file);
    
    fread(&taskCount, sizeof(int), 1, file);
    fread(tasks, sizeof(Task), taskCount, file);

    loadQueue(file);

    loadStack(file);

    fclose(file);
    printf("\033[32mSession loaded successfully!\033[0m\n");
}


void saveQueue(FILE* file) {
    int qSize = assemblyQueue.size;
    fwrite(&qSize, sizeof(int), 1, file);
    
    QueueNode* current = assemblyQueue.front;
    while(current) {
        fwrite(&current->task, sizeof(Task), 1, file);
        current = current->next;
    }
}

void loadQueue(FILE* file) {
    int qSize;
    fread(&qSize, sizeof(int), 1, file);
    
    for(int i = 0; i < qSize; i++) {
        Task task;
        fread(&task, sizeof(Task), 1, file);
        enqueue(task);
    }
}

void saveStack(FILE* file) {
    int stackSize = undoStack.size;
    fwrite(&stackSize, sizeof(int), 1, file);
    
    StackNode* current = undoStack.top;
    while(current) {
        fwrite(&current->task, sizeof(Task), 1, file);
        current = current->next;
    }
}

void loadStack(FILE* file) {
    int stackSize;
    fread(&stackSize, sizeof(int), 1, file);
    
    for(int i = 0; i < stackSize; i++) {
        Task task;
        fread(&task, sizeof(Task), 1, file);
        pushUndo(task);
    }
}