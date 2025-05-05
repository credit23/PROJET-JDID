#ifndef ROBOT_H
#define ROBOT_H

#include <time.h>

typedef enum { IDLE, WORKING, ERROR } RobotStatus;

typedef struct Robot {
    int id;
    char name[50];
    RobotStatus status;
    int tasksCompleted;
    time_t lastMaintenance;
    char tools[100];
} Robot;

// Function prototypes
void addRobot();
void editRobot(int id);
void deleteRobot(int id);
Robot* printRobot(int id);
void listAllRobots();
void searchRobbotsByStatus(RobotStatus status);
void resetRobotStatus(int id);
void showWorkHistory(Robot* robot);
Robot* viewRobotbyid(int id);

#endif