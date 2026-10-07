#include <stdio.h>
#include "../include/fiber.h"

void task1(void)
{
    int id = fiber_get_current_id();

    for (int i = 1; i <= 3; i++) {
        printf("[Fiber %d] Low priority - Step %d\n", id, i);
        fiber_yield();
    }

    printf("[Fiber %d] Completed\n", id);
}


void task2(void)
{
    int id = fiber_get_current_id();

    for (int i = 1; i <= 3; i++) {
        printf("[Fiber %d] HIGH priority - Step %d\n", id, i);
        fiber_yield();
    }

    printf("[Fiber %d] Completed\n", id);
}


void task3(void)
{
    int id = fiber_get_current_id();

    for (int i = 1; i <= 3; i++) {
        printf("[Fiber %d] Medium priority - Step %d\n", id, i);
        fiber_yield();
    }

    printf("[Fiber %d] Completed\n", id);
}


int main(void)
{
    printf("\n========================================\n");
    printf("       FiberLib Priority Demo\n");
    printf("========================================\n\n");

    fiber_init();

    /*
     * Create fibers with different priorities.
     *
     * Higher number = higher priority.
     */
    fiber_create(task1, 1);
    fiber_create(task2, 3);
    fiber_create(task3, 2);

    printf("\nFiber priorities:\n");
    printf("Fiber 1 -> Priority 1\n");
    printf("Fiber 2 -> Priority 3\n");
    printf("Fiber 3 -> Priority 2\n\n");

    printf("Starting Priority Scheduler...\n\n");

    /*
     * 1 = Priority Scheduling
     */
    scheduler_set_policy(1);

    scheduler_run();

    printf("\n========================================\n");
    printf("       All Fibers Completed\n");
    printf("========================================\n");

    return 0;
}
