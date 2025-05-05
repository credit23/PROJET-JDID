#ifndef NAV_H
#define NAV_H

#include "robot.h"
#include "task.h"
#include "queue.h"

/**
 * Display and handle the Manage Robots submenu, allowing
 * CRUD operations on robots.
 */
void managerobotssubmenu(void);

/**
 * Display and handle the Manage Tasks submenu, allowing
 * CRUD operations on tasks.
 */
void managetaskssubmenu(void);

/**
 * Display and handle the Task Queue control submenu,
 * including viewing, reordering, and clearing the queue.
 */
void controlQueueSubmenu(void);

#endif // NAV_H
