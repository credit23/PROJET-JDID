// ======== robot.h ========
#ifndef ROBOT_H
#define ROBOT_H

#include <time.h>

#define MAX_ROBOTS 1000  // Max number of robots supported

/** Current status of a robot */
typedef enum { IDLE, WORKING, ERROR } RobotStatus;

/**
 * Robot data structure:
 * - id: unique identifier
 * - name: descriptive name
 * - status: current RobotStatus
 * - tasksCompleted: count of tasks completed
 * - lastMaintenance: timestamp of last maintenance
 * - tools: comma-separated list of tools
 */
typedef struct Robot {
    int id;
    char name[50];
    RobotStatus status;
    int tasksCompleted;
    time_t lastMaintenance;
    char tools[100];
} Robot;

// Global robot array and count
extern Robot robots[MAX_ROBOTS];
extern int robotCount;

// Function prototypes for Robot management
/** Add a new robot via user input */
void addRobot(void);
/** Edit robot information by ID */
void editRobot(int id);
/** Delete robot record by ID */
void deleteRobot(int id);
/** View and print details for a specific robot */
void printRobotDetails(const Robot *robot);
/** List all robots in the system */
void listAllRobots(void);
/** Search and display robots matching a given status */
void searchRobotsByStatus(RobotStatus status);
/** Reset status and counters for a given robot ID */
void resetRobotStatus(int id);
/** Display a given robot's work history */
void showWorkHistory(const Robot *robot);
/** Retrieve pointer to Robot struct by ID, or NULL if not found */
Robot* viewRobotById(int id);

#endif // ROBOT_H


