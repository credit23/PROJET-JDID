
#ifndef TASK_H
#define TASK_H

#include <time.h>

#define MAX_TASKS 1000  // Max number of tasks supported

/** Current stage/status of a task */
typedef enum { PENDING, ACTIVE, COMPLETED } StageStatus;

/**
 * Task data structure:
 * - id: unique identifier
 * - description: details of the task
 * - stage: current StageStatus
 * - components: list of required component IDs
 * - robotAssigned: ID of assigned robot (-1 if none)
 * - startTime: timestamp when task started
 * - endTime: timestamp when task completed
 */
typedef struct Task {
    int id;
    char description[200];
    StageStatus stage;
    int components[10];
    int robotAssigned;
    time_t startTime;
    time_t endTime;
} Task;

// Global task array and count
extern Task tasks[MAX_TASKS];
extern int taskCount;

// Function prototypes for task management
/** Create a new task via user input */
void createTask(void);
/** Update an existing task by ID */
void updateTask(int id);
/** Delete a task by ID */
void deleteTask(int id);
/** Retrieve pointer to Task by ID, or NULL if not found */
Task* getTaskById(int id);
/** List all tasks in the system */
void listAllTasks(void);
/** Search and display tasks matching a given stage/status */
void searchTasksByStage(StageStatus status);
/** Print detailed information for a given task */
void printTaskDetails(const Task *task);
/** Assign a task to a robot (prompts for IDs) */
void assignTaskToRobot(void);

#endif // TASK_H