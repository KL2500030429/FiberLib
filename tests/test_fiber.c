#include <stdio.h>
#include <assert.h>

#include "../include/fiber.h"


/* =========================================================
   Test 1: Fiber creation
   ========================================================= */

void test_creation_task(void)
{
    printf("[TEST FIBER] Running creation task\n");
}


void test_fiber_creation(void)
{
    printf("\nTEST 1: Fiber Creation\n");

    fiber_init();

    int id1 = fiber_create(test_creation_task, 1);
    int id2 = fiber_create(test_creation_task, 1);

    assert(id1 >= 0);
    assert(id2 >= 0);
    assert(id1 != id2);

    printf("PASS: Fibers created successfully.\n");
}


/* =========================================================
   Test 2: Round-Robin scheduling
   ========================================================= */

static int rr_counter = 0;


void round_robin_task1(void)
{
    rr_counter++;

    fiber_yield();

    rr_counter++;
}


void round_robin_task2(void)
{
    rr_counter++;

    fiber_yield();

    rr_counter++;
}


void test_round_robin(void)
{
    printf("\nTEST 2: Round-Robin Scheduling\n");

    fiber_init();

    rr_counter = 0;

    fiber_create(round_robin_task1, 1);
    fiber_create(round_robin_task2, 1);

    scheduler_set_policy(0);

    scheduler_run();

    assert(rr_counter == 4);

    printf("PASS: Round-Robin scheduling executed correctly.\n");
}


/* =========================================================
   Test 3: Priority scheduling
   ========================================================= */

static int priority_first = -1;


void low_priority_task(void)
{
    if (priority_first == -1) {
        priority_first = 1;
    }
}


void high_priority_task(void)
{
    if (priority_first == -1) {
        priority_first = 3;
    }
}


void test_priority(void)
{
    printf("\nTEST 3: Priority Scheduling\n");

    fiber_init();

    priority_first = -1;

    fiber_create(low_priority_task, 1);
    fiber_create(high_priority_task, 3);

    scheduler_set_policy(1);

    scheduler_run();

    assert(priority_first == 3);

    printf("PASS: Highest-priority fiber executed first.\n");
}


/* =========================================================
   Test 4: Mutex synchronization
   ========================================================= */

static FiberMutex test_mutex;

static int shared_counter = 0;


void synchronization_task1(void)
{
    fiber_mutex_lock(&test_mutex);

    shared_counter++;

    fiber_mutex_unlock(&test_mutex);
}


void synchronization_task2(void)
{
    fiber_mutex_lock(&test_mutex);

    shared_counter++;

    fiber_mutex_unlock(&test_mutex);
}


void test_synchronization(void)
{
    printf("\nTEST 4: Mutex Synchronization\n");

    fiber_init();

    fiber_mutex_init(&test_mutex);

    shared_counter = 0;

    fiber_create(synchronization_task1, 1);
    fiber_create(synchronization_task2, 1);

    scheduler_set_policy(0);

    scheduler_run();

    assert(shared_counter == 2);

    printf("PASS: Mutex protected shared resource correctly.\n");
}


/* =========================================================
   Main test program
   ========================================================= */

int main(void)
{
    printf("\n========================================\n");
    printf("          FiberLib Test Suite\n");
    printf("========================================\n");

    test_fiber_creation();

    test_round_robin();

    test_priority();

    test_synchronization();

    printf("\n========================================\n");
    printf("       ALL TESTS PASSED SUCCESSFULLY\n");
    printf("========================================\n");

    return 0;
}
