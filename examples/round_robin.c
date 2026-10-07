#include <stdio.h>
#include "../include/fiber.h"

/*
 * Fiber 1 task
 */
void task1(void)
{
    for (int i = 1; i <= 4; i++) {
        printf("[Fiber 1] Executing step %d\n", i);
        fiber_yield();
    }

    printf("[Fiber 1] Completed\n");
}


/*
 * Fiber 2 task
 */
void task2(void)
{
    for (int i = 1; i <= 4; i++) {
        printf("[Fiber 2] Executing step %d\n", i);
        fiber_yield();
    }

    printf("[Fiber 2] Completed\n");
}


/*
 * Fiber 3 task
 */
void task3(void)
{
    for (int i = 1; i <= 4; i++) {
        printf("[Fiber 3] Executing step %d\n", i);
        fiber_yield();
    }

    printf("[Fiber 3] Completed\n");
}


/*
 * Main program
 */
int main(void)
{
    printf("\n========================================\n");
    printf("       FiberLib Round-Robin Demo\n");
    printf("========================================\n\n");

    fiber_init();

    /*
     * Create three fibers.
     */
    fiber_create(task1, 1);
    fiber_create(task2, 1);
    fiber_create(task3, 1);

    printf("\nStarting Round-Robin Scheduler...\n\n");

    /*
     * Select Round-Robin scheduling.
     */
    scheduler_set_policy(0);

    /*
     * Start scheduler.
     */
    scheduler_run();

    printf("\n========================================\n");
    printf("       All Fibers Completed\n");
    printf("========================================\n");

    return 0;
}
