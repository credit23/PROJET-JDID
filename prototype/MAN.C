#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "robot.h"
#include "task.h"
#include "queue.h"
#include "file_io.h"
#include "nav.h"
#include "production.h"

int main() {
    TreeNode* factoryTree = createFactoryTree();
    BSTNode* robotBST = NULL;
    Queue taskQueue;
    initQueue(&taskQueue);

    int choice;
    do {
        printf("\n--- Robotic Factory Assembly Line Manager ---\n");
        printf("1. Add Robot\n");
        printf("2. Search Robot\n");
        printf("3. Display All Robots (In-order Traversal)\n");
        printf("4. Add Task to Queue\n");
        printf("5. Assign Task to Robot\n");
        printf("6. Undo Last Task\n");
        printf("7. Display Task Queue\n");
        printf("8. Display Factory Tree\n");
        printf("9. Generate Production Summary\n");
        printf("10. Show Work History\n");
        printf("11. Save Session\n");
        printf("12. Load Session\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from buffer

        switch (choice) {
            case 1: {
                Robot robot = inputRobot();
                robotBST = insertRobotBST(robotBST, robot);
                printf("Robot added.\n");
                break;
            }
            case 2: {
                int id;
                printf("Enter Robot ID to search: ");
                scanf("%d", &id);
                BSTNode* result = searchRobotBST(robotBST, id);
                if (result) {
                    printf("Found: ID %d | Name: %s | Status: %d\n",
                           result->robot.id, result->robot.name, result->robot.status);
                } else {
                    printf("Robot not found.\n");
                }
                break;
            }
            case 3:
                inorderTraversalBST(robotBST);
                break;

            case 4: {
                Task task = inputTask();
                enqueue(&taskQueue, task);
                printf("Task added to queue.\n");
                break;
            }

            case 5:
                assignTaskToRobot(&taskQueue, robotBST);
                break;

            case 6:
                undoLastTask(&taskQueue);
                break;

            case 7:
                displayQueue(&taskQueue);
                break;

            case 8:
                displayFactoryTree(factoryTree, 0);
                break;

            case 9:
                generateProductionSummary(robotBST);
                break;

            case 10:
                showWorkHistory(); // Make sure this is implemented or stubbed
                break;

            case 11:
                if (saveSession("session.dat", factoryTree) == 0)
                    printf("Session saved.\n");
                else
                    printf("Failed to save session.\n");
                break;

            case 12: {
                TreeNode* loaded = loadSession("session.dat");
                if (loaded) {
                    freeFactoryTree(factoryTree); // Avoid memory leaks
                    factoryTree = loaded;
                    printf("Session loaded.\n");
                } else {
                    printf("Failed to load session.\n");
                }
                break;
            }

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 0);

    // Free memory
    freeFactoryTree(factoryTree);
    freeRobotBST(robotBST);
    freeQueue(&taskQueue);

    return 0;
}
