#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

#include "../include/fiber.h"

extern Fiber *fiber_get_by_id(int id);
extern int fiber_get_count(void);

#define SCHED_ROUND_ROBIN 0
#define SCHED_PRIORITY     1

static int scheduling_policy = SCHED_ROUND_ROBIN;

static Fiber *current_fiber = NULL;

static int next_fiber_index = 0;

static ucontext_t scheduler_context;


/*
 * Return the currently running fiber.
 */
Fiber *scheduler_get_current(void)
{
    return current_fiber;
}


/*
 * Set scheduler policy.
 */
void scheduler_set_policy(int policy)
{
    if (policy == SCHED_ROUND_ROBIN ||
        policy == SCHED_PRIORITY) {

        scheduling_policy = policy;
    }
}


/*
 * Round-Robin selection.
 */
static Fiber *select_round_robin(void)
{
    int count = fiber_get_count();

    if (count == 0) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {

        int index = (next_fiber_index + i) % count;

        Fiber *fiber = fiber_get_by_id(index);

        if (fiber != NULL &&
            fiber->state == FIBER_READY) {

            next_fiber_index = (index + 1) % count;

            return fiber;
        }
    }

    return NULL;
}


/*
 * Priority selection.
 */
static Fiber *select_priority(void)
{
    int count = fiber_get_count();

    Fiber *best = NULL;

    for (int i = 0; i < count; i++) {

        Fiber *fiber = fiber_get_by_id(i);

        if (fiber != NULL &&
            fiber->state == FIBER_READY) {

            if (best == NULL ||
                fiber->priority > best->priority) {

                best = fiber;
            }
        }
    }

    return best;
}


/*
 * Select next fiber.
 */
static Fiber *select_next_fiber(void)
{
    if (scheduling_policy == SCHED_PRIORITY) {
        return select_priority();
    }

    return select_round_robin();
}


/*
 * Start or continue scheduling.
 */
void scheduler_start(void)
{
    Fiber *previous = current_fiber;

    Fiber *next = select_next_fiber();

    /*
     * No READY fibers remain.
     */
    if (next == NULL) {

        current_fiber = NULL;

        /*
         * Return to scheduler_run().
         */
        setcontext(&scheduler_context);

        return;
    }


    /*
     * If switching from another fiber,
     * mark the previous one appropriately.
     */
    if (previous != NULL &&
        previous != next &&
        previous->state == FIBER_RUNNING) {

        previous->state = FIBER_READY;
    }


    /*
     * Select the new fiber.
     */
    next->state = FIBER_RUNNING;

    current_fiber = next;

    printf(
        "Scheduler: Switching to Fiber %d\n",
        next->id
    );


    /*
     * First fiber or returning from scheduler.
     */
    if (previous == NULL) {

        setcontext(&next->context);

    } else {

        fiber_switch_context(previous, next);
    }
}


/*
 * Run scheduler until all fibers finish.
 */
void scheduler_run(void)
{
    /*
     * Save the scheduler's execution context.
     */
    if (getcontext(&scheduler_context) == -1) {
        perror("getcontext");
        exit(EXIT_FAILURE);
    }


    /*
     * If no fibers are ready, finish.
     */
    Fiber *next = select_next_fiber();

    if (next == NULL) {

        current_fiber = NULL;

        printf("Scheduler: All fibers completed.\n");

        return;
    }


    /*
     * Start scheduling.
     */
    scheduler_start();


    /*
     * Execution returns here when the
     * scheduler context is restored.
     */
    if (current_fiber == NULL) {

        printf("Scheduler: All fibers completed.\n");

        return;
    }
}
