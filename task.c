#include "task.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "robot.h"

#define MAX_TASKS 100

Task tasks[MAX_TASKS];
static int taskCount = 0;

void createTask() {
    if(taskCount >= MAX_TASKS) {
        printf("\n\033[31mError: Maximum tasks reached!\033[0m\n");
        return;
    }

    Task newTask;
    newTask.id = taskCount + 1;
    
    printf("\nEnter task description: ");
    fgets(newTask.description, sizeof(newTask.description), stdin);
    newTask.description[strcspn(newTask.description, "\n")] = '\0';
    memset(newTask.components, 0, sizeof(newTask.components));
    printf("Enter component IDs (comma-separated, max 10): ");
    
    char input[256];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    char* token = strtok(input, ",");
    int compIndex = 0;
    
    while(token != NULL && compIndex < 10) {
        char* endptr;
        long component = strtol(token, &endptr, 10);
        
        if(*endptr == '\0' && component > 0) {
            newTask.components[compIndex++] = (int)component;
        } else {
            printf("\033[33mSkipping invalid component: %s\033[0m\n", token);
        }
        token = strtok(NULL, ",");
    }

    newTask.stage = PENDING;
    newTask.robotAssigned = -1; 
    newTask.startTime = time(NULL);
    newTask.endTime = 0;

    tasks[taskCount++] = newTask;
    
    printf("\n\033[32mTask created successfully!\033[0m");
    printf("\nID: %d | Components: %d | Status: PENDING\n", 
          newTask.id, compIndex);
}

void updateTask(int id) {
    int taskIndex = -1;

    for(int i = 0; i < taskCount; i++) {
        if(tasks[i].id == id) {
            taskIndex = i;
            break;
        }
    }
    if(taskIndex == -1) {
        printf("\n\033[31mError: Task %d not found!\033[0m\n", id);
        return;
    }
    Task* task = &tasks[taskIndex];
    int choice;
    do {
        printf("\n\033[36m=== Editing Task %d ===\033[0m\n", id);
        printf("1. Edit Description\n");
        printf("2. Update Components\n");
        printf("3. Change Status\n");
        printf("4. Mark as Completed\n");
        printf("6. Return to Menu\n");
        printf("Choose field to update: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice) {
            case 1: { 
                printf("Current description: %s\n", task->description);
                printf("New description: ");
                fgets(task->description, sizeof(task->description), stdin);
                task->description[strcspn(task->description, "\n")] = '\0';
                printf("\033[32mDescription updated!\033[0m\n");
                break;
            }
            
            case 2: { 
                printf("Current components: ");
                for(int i = 0; i < 10 && task->components[i] != 0; i++) {
                    printf("%d ", task->components[i]);
                }
                
                printf("\nEnter new components (comma-separated IDs): ");
                char input[256];
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                memset(task->components, 0, sizeof(task->components));

                char* token = strtok(input, ",");
                int compIndex = 0;
                
                while(token != NULL && compIndex < 10) {
                    char* endptr;
                    long component = strtol(token, &endptr, 10);
                    if(*endptr == '\0' && component > 0) {
                        task->components[compIndex++] = (int)component;
                    } else {
                        printf("\033[33mSkipping invalid component: %s\033[0m\n", token);
                    }
                    token = strtok(NULL, ",");
                }
                printf("\033[32mComponents updated! Total: %d\033[0m\n", compIndex);
                break;
            }
            
            case 3: {
                printf("Current status: %d\n", task->stage);
                printf("New status (0=PENDING, 1=ACTIVE, 2=COMPLETED): ");
                int newStatus;
                scanf("%d", &newStatus);
                while(getchar() != '\n');
                if(newStatus >= PENDING && newStatus <= COMPLETED) {
                    task->stage = newStatus;
                    if(newStatus == COMPLETED) {
                        task->endTime = time(NULL);
                    }
                    printf("\033[32mStatus updated!\033[0m\n");
                } else {
                    printf("\033[31mInvalid status!\033[0m\n");
                }
                break;
            }
            case 4: { 
                task->stage = COMPLETED;
                task->endTime = time(NULL);
                if(task->robotAssigned != -1) {
                    Robot* r = viewRobot(task->robotAssigned);
                    if(r != NULL) {
                        r->tasksCompleted++;
                        r->status = IDLE;
                    }
                }
                printf("\033[32mTask marked completed!\033[0m\n");
                break;
            }
            case 6:
                return;
            default:
                printf("\033[31mInvalid choice!\033[0m\n");
        }
    } while(choice != 6);
}

void deleteTask(int id) {
    if (taskCount <= 0) {
        printf("\n\033[31mError: No tasks to delete!\033[0m\n");
        return;
    }
    int foundIndex = -1;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1) {
        printf("\n\033[31mError: Task with ID %d not found!\033[0m\n", id);
        return;
    }
    for (int i = foundIndex; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    taskCount--; 
    printf("\n\033[32mTask %d successfully deleted!\033[0m\n", id);
}

Task* getTaskbyID(int id) {
    for(int i = 0; i < taskCount; i++) {
        if(tasks[i].id == id) {
            return &tasks[i]; 
        }
    }
    return NULL;
}

void listAllTasks() {
    if(taskCount == 0) {
        printf("\n\033[31mNo tasks in the system!\033[0m\n");
        return;
    }
    printf("\n\033[36m=== All Tasks (%d total) ===\033[0m\n", taskCount);
    for(int i = 0; i < taskCount; i++) {
        Task t = tasks[i];
        char timeBuf[20];
        char statusStr[10];
        switch(t.stage) {
            case PENDING: strcpy(statusStr, "PENDING"); break;
            case ACTIVE: strcpy(statusStr, "ACTIVE"); break;
            case COMPLETED: strcpy(statusStr, "COMPLETED"); break;
            default: strcpy(statusStr, "UNKNOWN");
        }
        strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", 
                localtime(&t.startTime));
        printf("\n\033[33mTask ID: %d\033[0m\n", t.id);
        printf("Description:   %s\n", t.description);
        printf("Status:        %s\n", statusStr);
        printf("Start Time:    %s\n", timeBuf);
        if(t.stage == COMPLETED) {
            strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", 
                    localtime(&t.endTime));
            printf("End Time:      %s\n", timeBuf);
        } else {
            printf("End Time:      N/A\n");
        }
        printf("Components (%d): ", countComponents(t.components));
        for(int j = 0; j < 10; j++) {
            if(t.components[j] != 0) {
                printf("%d ", t.components[j]);
            }
        }
        if(t.robotAssigned != -1) {
            printf("\nAssigned Robot: %d", t.robotAssigned);
            Robot* r = viewRobot(t.robotAssigned);
            if(r) printf(" (%s)", r->name);
        }
        
        printf("\n\033[90m---------------------------------\033[0m\n");
    }
}
int countComponents(int components[10]) {
    int count = 0;
    for(int i = 0; i < 10; i++) {
        if(components[i] != 0) count++;
    }
    return count;
}

void printTaskDetails(Task task) {
    printf("\n\033[33m=== Task Details ===\033[0m\n");
    printf("\033[36mID:\033[0m            %d\n", task.id);
    printf("\033[36mDescription:\033[0m   %s\n", task.description);
    char* status;
    switch(task.stage) {
        case PENDING:   status = "PENDING"; break;
        case ACTIVE:    status = "ACTIVE"; break;
        case COMPLETED: status = "COMPLETED"; break;
        default:        status = "UNKNOWN";
    }
    printf("\033[36mStatus:\033[0m        %s\n", status);
    char timeBuf[20];
    strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", localtime(&task.startTime));
    printf("\033[36mStart Time:\033[0m    %s\n", timeBuf);
    
    if(task.stage == COMPLETED) {
        strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", localtime(&task.endTime));
        printf("\033[36mEnd Time:\033[0m      %s\n", timeBuf);
    } else {
        printf("\033[36mEnd Time:\033[0m      -\n");
    }
    printf("\033[36mComponents:\033[0m   ");
    int componentsShown = 0;
    for(int i = 0; i < 10; i++) {
        if(task.components[i] != 0) {
            printf("%d ", task.components[i]);
            componentsShown++;
        }
    }
    if(componentsShown == 0) printf("None");
    printf("\n\033[36mAssigned Robot:\033[0m ");
    if(task.robotAssigned != -1) {
        Robot* r = viewRobot(task.robotAssigned);
        if(r) {
            printf("%d - %s", r->id, r->name);
        } else {
            printf("\033[31mInvalid robot (%d)\033[0m", task.robotAssigned);
        }
    } else {
        printf("Unassigned");
    }
    printf("\n\033[33m=====================\033[0m\n\n");
}

void assignTaskToRobot() {
    int taskId, robotId;
    printf("\nEnter Task ID to assign: ");
    if(scanf("%d", &taskId) != 1) {
        printf("\033[31mInvalid task ID!\033[0m\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');
    Task* task = getTask(taskId);
    if(!task) {
        printf("\033[31mTask %d not found!\033[0m\n", taskId);
        return;
    }
    if(task->stage == COMPLETED) {
        printf("\033[31mCannot assign robot to completed task!\033[0m\n");
        return;
    }
    printf("Enter Robot ID to assign: ");
    if(scanf("%d", &robotId) != 1) {
        printf("\033[31mInvalid robot ID!\033[0m\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');
    Robot* robot = viewRobot(robotId);
    if(!robot) {
        printf("\033[31mRobot %d not found!\033[0m\n", robotId);
        return;
    }
    if(robot->status != IDLE) {
        printf("\033[31mRobot %d is not available! Current status: ", robotId);
        switch(robot->status) {
            case WORKING: printf("WORKING\033[0m\n"); break;
            case ERROR: printf("ERROR\033[0m\n"); break;
            default: printf("UNKNOWN\033[0m\n");
        }
        return;
    }
    if(task->robotAssigned != -1) {
        printf("\033[33mTask already assigned to robot %d. Override? (y/n): \033[0m", 
              task->robotAssigned);
        char choice = getchar();
        while(getchar() != '\n');
        
        if(choice != 'y' && choice != 'Y') {
            printf("\033[33mAssignment canceled\033[0m\n");
            return;
        }
        Robot* prevRobot = viewRobot(task->robotAssigned);
        if(prevRobot) {
            prevRobot->status = IDLE;
            printf("\033[33mUnassigned robot %d\033[0m\n", prevRobot->id);
        }
    }
    task->robotAssigned = robotId;
    robot->status = WORKING;
    if(task->stage == PENDING) {
        task->stage = ACTIVE;
        task->startTime = time(NULL);
    }
    printf("\n\033[32mAssignment successful!\033[0m\n");
    printf("Task %d ('%s')\n", task->id, task->description);
    printf("Assigned to Robot %d ('%s')\n", robot->id, robot->name);
    printf("New Status: \033[33mACTIVE\033[0m\n");
}
