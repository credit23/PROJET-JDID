#include "production.h"
#include "task.h"
#include "robot.h"
#include <stdio.h>
#include <time.h>

// Extern declarations for global data
extern Task tasks[MAX_TASKS];
extern Robot robots[MAX_ROBOTS];
extern int taskCount;
extern int robotCount;

void generateProductionSummary(void) {
    if (taskCount == 0) {
        printf("\n\033[31mNo production data available!\033[0m\n");
        return;
    }

    // Task statistics
    int totalTasks     = taskCount;
    int completedTasks = 0;
    int pendingTasks   = 0;
    int activeTasks    = 0;
    double totalProdTimeSec = 0.0;

    for (int i = 0; i < taskCount; i++) {
        switch (tasks[i].stage) {
            case COMPLETED:
                completedTasks++;
                if (tasks[i].endTime > tasks[i].startTime) {
                    totalProdTimeSec += difftime(tasks[i].endTime, tasks[i].startTime);
                }
                break;
            case ACTIVE:
                activeTasks++;
                break;
            case PENDING:
                pendingTasks++;
                break;
            default:
                break;
        }
    }

    // Robot statistics
    int totalRobots    = robotCount;
    int workingRobots  = 0;
    int idleRobots     = 0;
    int errorRobots    = 0;
    double totalOpTimeSec = 0.0;
    time_t now = time(NULL);

    for (int i = 0; i < robotCount; i++) {
        totalOpTimeSec += difftime(now, robots[i].lastMaintenance);
        switch (robots[i].status) {
            case WORKING: workingRobots++; break;
            case IDLE:    idleRobots++;    break;
            case ERROR:   errorRobots++;   break;
            default:                    break;
        }
    }

    // KPIs
    double avgTaskTimeMin = completedTasks > 0 ? (totalProdTimeSec / completedTasks) / 60.0 : 0.0;
    double efficiencyPct = totalOpTimeSec > 0 ? (totalProdTimeSec / totalOpTimeSec) * 100.0 : 0.0;

    // Output summary
    printf("\n\033[36m============ Production Summary ============\033[0m\n");

    printf("\n\033[33mTasks:\033[0m\n");
    printf(" Total:        %d\n", totalTasks);
    if (totalTasks > 0) {
        printf(" Completed:    %d (%.1f%%)\n", completedTasks,
               (double)completedTasks / totalTasks * 100.0);
    } else {
        printf(" Completed:    %d\n", completedTasks);
    }
    printf(" Active:       %d\n", activeTasks);
    printf(" Pending:      %d\n", pendingTasks);

    printf("\n\033[33mRobots:\033[0m\n");
    printf(" Total:        %d\n", totalRobots);
    printf(" Working:      %d\n", workingRobots);
    printf(" Idle:         %d\n", idleRobots);
    printf(" Error:        %d\n", errorRobots);
    printf(" Total Op.Time: %.1f hours\n", totalOpTimeSec / 3600.0);

    printf("\n\033[33mPerformance:\033[0m\n");
    printf(" Avg Task Time:  %.1f minutes\n", avgTaskTimeMin);
    printf(" Efficiency:     %.1f%%\n", efficiencyPct);
    printf(" Total Prod.Time: %.1f hours\n", totalProdTimeSec / 3600.0);

    printf("\033[36m============================================\033[0m\n");
}
