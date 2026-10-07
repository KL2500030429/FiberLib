#include <stdio.h>
#include "../include/fiber.h"

void task1(void)
{
    int id = fiber_get_current_id();

    for (int i = 1; i <= 3; i++) {
        printf("[Fiber %d] Step %d\n", id, i);
        fiber_yield();
    }

    printf("[Fiber %d] Finished\n", id);
}


void task2(void)
{
    int id = fiber_get_current_id();

    for (int i = 1; i <= 3; i++) {
        printf("[Fiber %d] Step %d\n", id, i);
        fiber_yield();
    }

    printf("[Fiber %d] Finished\n", id);
}

/*
 * Main function
 */
int main(void)
{
    printf("=================================\n");
    printf("      FiberLib Basic Demo\n");
    printf("=================================\n\n");

    /*
     * Initialize FiberLib.
     */
    fiber_init();

    /*
     * Create two fibers.
     */
    int f1 = fiber_create(task1, 1);
    int f2 = fiber_create(task2, 1);

    if (f1 < 0 || f2 < 0) {
        printf("Failed to create fibers.\n");
        return 1;
    }

    printf("\nStarting scheduler...\n\n");

    /*
     * Start the scheduler.
     */
    scheduler_run();

    /*
     * Wait for both fibers.
     */
    fiber_join(f1);
    fiber_join(f2);

    printf("\n=================================\n");
    printf("All fibers completed.\n");
    printf("=================================\n");

    return 0;
}
