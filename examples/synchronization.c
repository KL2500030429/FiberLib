#include <stdio.h>
#include "../include/fiber.h"

/*
 * Shared resource.
 */
static int shared_counter = 0;

/*
 * Mutex for protecting the shared resource.
 */
static FiberMutex mutex;


/*
 * Fiber 1
 */
void task1(void)
{
    for (int i = 1; i <= 3; i++) {

        fiber_mutex_lock(&mutex);

        printf("[Fiber 1] Entering critical section\n");

        int temp = shared_counter;

        printf("[Fiber 1] Counter before: %d\n", temp);

        temp++;

        shared_counter = temp;

        printf("[Fiber 1] Counter after: %d\n", shared_counter);

        printf("[Fiber 1] Leaving critical section\n");

        fiber_mutex_unlock(&mutex);

        fiber_yield();
    }

    printf("[Fiber 1] Completed\n");
}


/*
 * Fiber 2
 */
void task2(void)
{
    for (int i = 1; i <= 3; i++) {

        fiber_mutex_lock(&mutex);

        printf("[Fiber 2] Entering critical section\n");

        int temp = shared_counter;

        printf("[Fiber 2] Counter before: %d\n", temp);

        temp++;

        shared_counter = temp;

        printf("[Fiber 2] Counter after: %d\n", shared_counter);

        printf("[Fiber 2] Leaving critical section\n");

        fiber_mutex_unlock(&mutex);

        fiber_yield();
    }

    printf("[Fiber 2] Completed\n");
}


/*
 * Main program
 */
int main(void)
{
    printf("\n========================================\n");
    printf("      FiberLib Synchronization Demo\n");
    printf("========================================\n\n");

    /*
     * Initialize FiberLib.
     */
    fiber_init();

    /*
     * Initialize mutex.
     */
    fiber_mutex_init(&mutex);

    /*
     * Create two fibers.
     */
    fiber_create(task1, 1);
    fiber_create(task2, 1);

    printf("Shared counter initially: %d\n\n", shared_counter);

    printf("Starting scheduler...\n\n");

    /*
     * Use Round-Robin scheduling.
     */
    scheduler_set_policy(0);

    scheduler_run();

    printf("\n========================================\n");
    printf("Final shared counter: %d\n", shared_counter);
    printf("========================================\n");

    return 0;
}
