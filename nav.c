#include "nav.h"
#include <stdio.h>
#include "robot.h"
#include "task.h"
#include <string.h>
#include <stdlib.h>


void managerobotssubmenu(){
    int choice;
    do {
       
        printf("\n\033[36m===\033[33m 🤖 Manage Robots\033[36m ===\n"); 
        printf("\033[36m1.\033[97m ➕  Add New Robot\n");
        printf("\033[36m2.\033[97m ✏️   Edit Robot Information\n");
        printf("\033[36m3.\033[97m 🗑️   Delete Robot\n");
        printf("\033[36m4.\033[97m 🔍  View Robot by ID\n");
        printf("\033[36m5.\033[97m 📜  List All Robots\n");
        printf("\033[36m6.\033[97m 🚦  Search by Status (Idle/Working/Error)\n");
        printf("\033[36m7.\033[97m 📅  Show Work History\n");
        printf("\033[36m8.\033[97m 🔄  Reset Robot Status\n");
        printf("\033[36m9.\033[97m ↩️   Return to Main Menu\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        switch(choice) {
            case 1:
                addRobot();
                break;
                
            case 2: {
                int id;
                printf("Enter Robot ID to edit: ");
                scanf("%d", &id);
                while(getchar() != '\n');
                editRobot(id);
                break;
            }
                
            case 3: {
                int id;
                printf("Enter Robot ID to delete: ");
                scanf("%d", &id);
                while(getchar() != '\n');
                deleteRobot(id);
                break;
            }
                
            case 4: {
                int id;
                printf("Enter Robot ID to view: ");
                scanf("%d", &id);
                while(getchar() != '\n');
                
                Robot* robot = viewRobotbyid(id);
                if(robot != NULL) {
                    printRobotDetails(*robot);
                } else {
                    printf("\033[31mRobot with ID %d not found!\033[0m\n", id);
                }
                break;
            }
                
            case 5:
                listAllRobots();
                break;
                
            case 6: {
                    int status;
                    printf("Enter status (0-IDLE, 1-WORKING, 2-ERROR): ");
                    scanf("%d", &status);
                    while(getchar() != '\n'); 
                    searchRobotsByStatus(status);
                    break;
            }
            case 7: {
                int id;
                printf("Enter Robot ID: ");
                scanf("%d", &id);
                while(getchar() != '\n');
                showWorkHistory(viewRobotbyid(id));
                break;
            }
                
            case 8: {
                int id;
                printf("Enter Robot ID: ");
                scanf("%d", &id);
                while(getchar() != '\n');
                resetRobotStatus(id);
                break;
            }
                
            case 9:
                return;
                
            default:
                printf("\033[31mInvalid choice! Try 1-9.\033[0m\n");
                break;
        }
    } while(choice != 9);
}


void managetaskssubmenu(){
    int choice;
    do{
    printf("\n\033[36m===\033[33m 📋 Manage Tasks\033[36m ===\033[0m\n");
    printf("\033[36m1.\033[97m ➕ Create New Task\033[0m\n");
    printf("\033[36m2.\033[97m ✏️  Update Task\033[0m\n");
    printf("\033[36m3.\033[97m 🗑️  Delete Task\033[0m\n");
    printf("\033[36m4.\033[97m 🔍 View Task Details\033[0m\n");
    printf("\033[36m5.\033[97m 📜 List All Tasks\033[0m\n");
    printf("\033[36m6.\033[97m 🚦 Search by Stage (0-PENDING, 1-ACTIVE, 2-COMPLETED)\033[0m\n");
    printf("\033[36m7.\033[97m ↩️  Return to Main Menu\033[0m\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch(choice){
        case 1: createTask(); break;
        case 2: {
            int taskId;
            printf("Enter task ID to update: ");
            scanf("%d", &taskId);
            while(getchar() != '\n');
            updateTask(taskId);
            break;
        }
        case 3: {
            int taskId;
            printf("Enter task ID to delete: ");
            scanf("%d", &taskId);
            while(getchar() != '\n');
            deleteTask(taskId);
            break;
        }
        case 4:{
            int id;
            printf("Enter Task ID to view: ");
            scanf("%d", &id);
            while(getchar() != '\n');
            
            Task *task = getTaskbyID(id);
            if(task != NULL) {
                printTaskDetails(*task);
            } else {
                printf("\033[31mTask with ID %d not found!\033[0m\n", id);
            }
            break;
        }
            
        case 5:listAllTasks(); break;
        case 6: { 
            int status;
            printf("Enter status (0=PENDING, 1=ACTIVE, 2=COMPLETED): ");
            scanf("%d", &status);
            while(getchar() != '\n');
            searchTasksByStage(status);
            break;
        }
        case 7: break;
        default: printf("Invalid choice! Try 1-7. \n");
        }
    }while(choice!=7);
}

void controlqueuesubmenu(){
    int choice;
    do{
    printf("\n\033[36m===\033[33m 🚦 Task Queue Control\033[36m ===\033[0m\n");
    printf("\033[36m1.\033[97m 👀 View Queue\033[0m\n");
    printf("\033[36m2.\033[97m ➕ Add Task to Queue\033[0m\n");
    printf("\033[36m3.\033[97m ⏭️ Process Next Task\033[0m\n");
    printf("\033[36m4.\033[97m 🧹 Clear Queue\033[0m\n");
    printf("\033[36m5.\033[97m ↩️ Return to Main Menu\033[0m\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch(choice){
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        default: printf("Invalid choice! Try 1-7. \n");
        }
    }while(choice!=7);
}
