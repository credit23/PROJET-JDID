#ifndef TASK_H
#define TASK_H

#include <time.h>

typedef enum { PENDING, ACTIVE, COMPLETED } StageStatus;

typedef struct Task {
    int id;
    char description[200];
    StageStatus stage;
    int components[10];
    int robotAssigned;
    time_t startTime;
    time_t endTime;
} Task;

// Function prototypes
void createTask();
void updateTask(int id);
void deleteTask(int id);
Task* getTask(int id);
void listAllTasks();
void searchTasksByStage(StageStatus status);
void printTaskDetails(Task task);
void assignTaskToRobot();

#endif