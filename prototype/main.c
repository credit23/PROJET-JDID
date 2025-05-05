#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "nav.h"
#include "task.h"
#include "tree.h"
#include "queue.h"
#include "production.h"



int main() {
    TreeNode* factoryTree = createFactoryTree();  // Correct initialization
    int choice;
    
    do {
        printf("\033[36m\n===============\033[33m RFALM Menu\033[36m ===============\n");
        printf("\033[36m1.\033[97m    Manage Robots \n");
        printf("\033[36m2.\033[97m    Manage Tasks \n");
        printf("\033[36m3.\033[97m    View & Control Task Queue \n");
        printf("\033[36m4.\033[97m    Assign Task to Robot \n");
        printf("\033[36m5.\033[97m    Undo Last Task (Stack) \n");
        printf("\033[36m6.\033[97m    Display Factory Structure Tree \n");
        printf("\033[36m7.\033[97m    View Production Summary \n");
        printf("\033[36m8.\033[97m    Save Session to File \n");
        printf("\033[36m9.\033[97m    Load Session from File \n");
        printf("\033[36m10.\033[97m   Exit \n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice) {
            case 1: managerobotssubmenu(); break;  // Correct function name
            case 2: managetaskssubmenu(); break;
            case 3: controlQueueSubmenu(); break;
            case 4: assignTaskToRobot(); break;
            case 5: {
                Task undoneTask = popUndo();
                if(undoneTask.id != -1) {
                    enqueue(undoneTask);
                    printf("Undid task %d\n", undoneTask.id);
                }
                break;
            }
            case 6: displayFactoryTree(factoryTree, 0); break;
            case 7: generateProductionSummary(); break;
            case 8: printf("Exiting...\n"); break;
            case 9: printf("Exiting...\n"); break;
            case 10: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 10);

    // Cleanup



    

    return 0;
}