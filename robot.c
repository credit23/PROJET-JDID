#include "robot.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_ROBOTS 1000

Robot robots[MAX_ROBOTS];
static int robotCount = 0;

void addRobot() {
    if(robotCount >= MAX_ROBOTS) {
        printf("Maximum robots reached!\n");
        return;
    } 
    
    Robot newRobot;
    newRobot.id = robotCount + 1;
    
    printf("Enter robot name: ");
    fgets(newRobot.name, 50, stdin);
    newRobot.name[strcspn(newRobot.name, "\n")] = '\0';
    
    printf("Enter tools (comma-separated): ");
    fgets(newRobot.tools, 100, stdin);
    newRobot.tools[strcspn(newRobot.tools, "\n")] = '\0';
    
    newRobot.status = IDLE;
    newRobot.tasksCompleted = 0;
    newRobot.lastMaintenance = time(NULL);
    
    robots[robotCount++] = newRobot;
    printf("Robot added! ID: %d\n", newRobot.id);
}

void editRobot(int id) {
    int found = 0;
    int index = -1;

    for(int i = 0; i < robotCount; i++) {
        if(robots[i].id == id) {
            found = 1;
            index = i;
            break;
        }
    }

    if(!found) {
        printf("\n❌ Error: Robot with ID %d not found!\n", id);
        return;
    }

    int choice;
    char buffer[100];
    
    do {
        printf("\n=== Editing Robot ID %d ===\n", id);
        printf("1. Edit Name\n");
        printf("2. Edit Tools\n");
        printf("3. Return to Previous Menu\n");
        printf("Choose field to edit: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice) {
            case 1:
                printf("Current name: %s\n", robots[index].name);
                printf("Enter new name: ");
                fgets(buffer, sizeof(robots[index].name), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                strncpy(robots[index].name, buffer, 49);
                robots[index].name[49] = '\0';
                printf("✅ Name updated successfully!\n");
                break;

            case 2:
                printf("Current tools: %s\n", robots[index].tools);
                printf("Enter new tools (comma-separated): ");
                fgets(buffer, sizeof(robots[index].tools), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                strncpy(robots[index].tools, buffer, 99);
                robots[index].tools[99] = '\0';
                printf("✅ Tools updated successfully!\n");
                break;

            case 3:
                printf("↩️ Returning to previous menu...\n");
                break;

            default:
                printf("❌ Invalid choice! Please try again.\n");
        }
    } while(choice != 3);
}



void deleteRobot(int id) {
    if(robotCount <= 0) {
        printf("Error: No robots to delete!\n", id);
        return;
    }
    int found = -1;
    for(int i = 0; i < robotCount; i++) {
        if(robots[i].id == id) {
            found = i;
            break;
        }
    }

    if(found == -1) {
        printf("\n❌ Error: Robot with ID %d not found!\n", id);
        return;
    }

    for(int i = found; i < robotCount - 1; i++) {
        robots[i] = robots[i + 1];
    }

    robotCount--;
    printf("Robot ID %d successfully deleted!\n", id);
}

void printRobotDetails(Robot robot){
    printf("\n=== Robot Details ===\n");
    printf("ID:            %d\n", robot.id);
    printf("Name:          %s\n", robot.name);
    
    char* status;
    switch(robot.status) {
        case IDLE:    status = "IDLE"; break;
        case WORKING: status = "WORKING"; break;
        case ERROR:   status = "ERROR"; break;
        default:      status = "UNKNOWN";
    }
    printf("Status:        %s\n", status);
    
    printf("Tasks Completed: %d\n", robot.tasksCompleted);
    
    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", 
            localtime(&robot.lastMaintenance));
    printf("Last Maintenance: %s\n", timeStr);
    
    printf("Tools:         %s\n", robot.tools);
    printf("==========================\n");
}

Robot* viewRobotbyid(int id) {
    for(int i = 0; i < robotCount; i++) {
        if(robots[i].id == id) {
            return &robots[i];
        }
    }
    return NULL;
}

void listAllRobots() {
    if(robotCount == 0) {
        printf("\n\033[31mNo robots in the system!\033[0m\n");
        return;
    }

    printf("\n\033[36m=== All Robots (%d total) ===\033[0m\n", robotCount);
    for(int i = 0; i < robotCount; i++) {
        printf("\nRobot %d/%d\n", i+1, robotCount);
        printRobotDetails(robots[i]);
    }
    printf("\n\033[36m=============================\033[0m\n");
}

void searchRobotsByStatus(RobotStatus status) {
    if(status < IDLE || status > ERROR) {
        printf("\n\033[31mInvalid status code!\033[0m\n");
        return;
    }

    if(robotCount == 0) {
        printf("\n\033[31mNo robots in the system!\033[0m\n");
        return;
    }

    char* statusName;
    switch(status) {
        case IDLE:    statusName = "IDLE"; break;
        case WORKING: statusName = "WORKING"; break;
        case ERROR:   statusName = "ERROR"; break;
    }

    printf("\n\033[36m=== Robots in %s Status ===\033[0m\n", statusName);
    
    int found = 0;
    for(int i = 0; i < robotCount; i++) {
        if(robots[i].status == status) {
            printRobotDetails(robots[i]);
            found++;
        }
    }

    if(!found) {
        printf("\033[33mNo robots found in %s status!\033[0m\n", statusName);
    } else {
        printf("\n\033[36mTotal: %d robot(s)\033[0m\n", found);
    }
}

void resetRobotStatus(int id) {
    int found = 0;
    
    for(int i = 0; i < robotCount; i++) {
        if(robots[i].id == id) {
            robots[i].status = IDLE;
            robots[i].lastMaintenance = time(NULL);
            found = 1;
            break;
        }
    }

    if(found) {
        printf("\n\033[32m✅ Robot %d status reset to IDLE\033[0m\n", id);
        printf("\033[33mMaintenance timestamp updated\033[0m\n");
    } else {
        printf("\n\033[31m❌ Error: Robot %d not found!\033[0m\n", id);
    }
}

