#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

#include "../include/fiber.h"

/* Functions provided by scheduler.c */
extern Fiber *scheduler_get_current(void);
extern void scheduler_start(void);

/* Fiber storage */
static Fiber fibers[MAX_FIBERS];

static int fiber_count = 0;
static int current_fiber_id = -1;


/*
 * Initialize FiberLib.
 */
void fiber_init(void)
{
    fiber_count = 0;
    current_fiber_id = -1;

    queue_init();

    for (int i = 0; i < MAX_FIBERS; i++) {
        fibers[i].id = -1;
        fibers[i].state = FIBER_TERMINATED;
        fibers[i].stack = NULL;
        fibers[i].function = NULL;
        fibers[i].priority = 0;
    }
}


/*
 * Wrapper executed by every fiber.
 */
static void fiber_wrapper(int fiber_id)
{
    current_fiber_id = fiber_id;

    fibers[fiber_id].state = FIBER_RUNNING;

    fibers[fiber_id].function();

    fiber_exit();
}


/*
 * Create a new fiber.
 */
int fiber_create(void (*function)(void), int priority)
{
    if (fiber_count >= MAX_FIBERS) {
        printf("Error: Maximum number of fibers reached.\n");
        return -1;
    }

    if (function == NULL) {
        printf("Error: Fiber function cannot be NULL.\n");
        return -1;
    }

    int id = fiber_count;

    fibers[id].id = id;
    fibers[id].state = FIBER_READY;
    fibers[id].function = function;
    fibers[id].priority = priority;

    fibers[id].stack = malloc(FIBER_STACK_SIZE);

    if (fibers[id].stack == NULL) {
        perror("malloc");
        return -1;
    }

    if (getcontext(&fibers[id].context) == -1) {
        perror("getcontext");

        free(fibers[id].stack);
        fibers[id].stack = NULL;

        return -1;
    }

    fibers[id].context.uc_stack.ss_sp = fibers[id].stack;
    fibers[id].context.uc_stack.ss_size = FIBER_STACK_SIZE;
    fibers[id].context.uc_stack.ss_flags = 0;
    fibers[id].context.uc_link = NULL;

    makecontext(
        &fibers[id].context,
        (void (*)(void))fiber_wrapper,
        1,
        id
    );

    if (queue_push(&fibers[id]) != 0) {
        printf("Error: Ready queue is full.\n");

        free(fibers[id].stack);
        fibers[id].stack = NULL;

        return -1;
    }

    fiber_count++;

    printf("Fiber %d created successfully.\n", id);

    return id;
}


/*
 * Yield the CPU voluntarily.
 */
void fiber_yield(void)
{
    Fiber *current = scheduler_get_current();

    if (current == NULL) {
        return;
    }

    current->state = FIBER_READY;

    scheduler_start();
}


/*
 * Terminate the current fiber.
 */
void fiber_exit(void)
{
    Fiber *current = scheduler_get_current();

    if (current == NULL) {
        return;
    }

    current->state = FIBER_TERMINATED;

    printf("Fiber %d terminated.\n", current->id);

    scheduler_start();
}


/*
 * Wait until a fiber terminates.
 */
void fiber_join(int fiber_id)
{
    if (fiber_id < 0 || fiber_id >= fiber_count) {
        printf("Invalid fiber ID.\n");
        return;
    }

    while (fibers[fiber_id].state != FIBER_TERMINATED) {
        scheduler_start();
    }

    printf("Fiber %d joined successfully.\n", fiber_id);

    if (fibers[fiber_id].stack != NULL) {
        free(fibers[fiber_id].stack);
        fibers[fiber_id].stack = NULL;
    }
}


/*
 * Return current fiber ID.
 */
int fiber_get_current_id(void)
{
    return current_fiber_id;
}


/*
 * Get fiber by ID.
 */
Fiber *fiber_get_by_id(int id)
{
    if (id < 0 || id >= fiber_count) {
        return NULL;
    }

    return &fibers[id];
}


/*
 * Return number of fibers.
 */
int fiber_get_count(void)
{
    return fiber_count;
}


/*
 * Initialize a fiber mutex.
 */
void fiber_mutex_init(FiberMutex *mutex)
{
    if (mutex == NULL) {
        return;
    }

    mutex->locked = 0;
    mutex->owner = -1;
}


/*
 * Lock the mutex.
 */
void fiber_mutex_lock(FiberMutex *mutex)
{
    if (mutex == NULL) {
        return;
    }

    int current_id = fiber_get_current_id();

    while (mutex->locked) {
        fiber_yield();
    }

    mutex->locked = 1;
    mutex->owner = current_id;

    printf("Fiber %d acquired the mutex.\n", current_id);
}


/*
 * Unlock the mutex.
 */
void fiber_mutex_unlock(FiberMutex *mutex)
{
    if (mutex == NULL) {
        return;
    }

    int current_id = fiber_get_current_id();

    if (mutex->locked && mutex->owner == current_id) {

        mutex->locked = 0;
        mutex->owner = -1;

        printf("Fiber %d released the mutex.\n", current_id);
    }
}
