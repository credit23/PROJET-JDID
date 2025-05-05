#include "production.h"
#include "task.h"
#include "robot.h"
#include <stdio.h>
#include <time.h>

void generateProductionSummary() {
    if(taskCount == 0 && robotCount == 0) {
        printf("\n\033[31mNo production data available!\033[0m\n");
        return;
    }
//----task statistics
    int totalTasks = taskCount;
    int completedTasks = 0;
    int pendingTasks = 0;
    int activeTasks = 0;
    double totalProductionTime = 0;

    for(int i = 0; i < taskCount; i++) {
        switch(tasks[i].stage) {
            case COMPLETED:
                completedTasks++;
                if(tasks[i].endTime > tasks[i].startTime) {
                    totalProductionTime += difftime(tasks[i].endTime, tasks[i].startTime);
                }
                break;
            case ACTIVE:
                activeTasks++;
                break;
            case PENDING:
                pendingTasks++;
                break;
        }
    }

//-----robot statistics
    int totalRobots = robotCount;
    int activeRobots = 0;
    int idleRobots = 0;
    int errorRobots = 0;
    double totalOperationalTime = 0;

    for(int i = 0; i < robotCount; i++) {
        totalOperationalTime += difftime(time(NULL), robots[i].lastMaintenance);
        
        switch(robots[i].status) {
            case WORKING: activeRobots++; break;
            case IDLE: idleRobots++; break;
            case ERROR: errorRobots++; break;
        }
    }

//---kpi
    double avgTaskTime = completedTasks > 0 ? totalProductionTime / completedTasks : 0;
    double efficiency = completedTasks > 0 ? 
        (totalProductionTime / (activeRobots * totalOperationalTime)) * 100 : 0;

    printf("\n\033[36m============ Production Summary ============\033[0m\n");
    

    printf("\n\033[33mTasks:\033[0m\n");
    printf(" Total:        %d\n", totalTasks);
    printf(" Completed:    %d (%.1f%%)\n", completedTasks, 
          (double)completedTasks/totalTasks*100);
    printf(" Active:       %d\n", activeTasks);
    printf(" Pending:      %d\n", pendingTasks);

    printf("\n\033[33mRobots:\033[0m\n");
    printf(" Total:        %d\n", totalRobots);
    printf(" Working:      %d\n", activeRobots);
    printf(" Idle:         %d\n", idleRobots);
    printf(" In Error:     %d\n", errorRobots);
    printf(" Total Op.Time:%.1f hours\n", totalOperationalTime/3600);
    
    printf("\n\033[33mPerformance:\033[0m\n");
    printf(" Avg Task Time:  %.1f minutes\n", avgTaskTime/60);
    printf(" Efficiency:     %.1f%%\n", efficiency);
    printf(" Total Prod.Time:%.1f hours\n", totalProductionTime/3600);
    
    printf("\033[36m============================================\033[0m\n");
}