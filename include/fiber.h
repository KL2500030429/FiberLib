#ifndef FIBER_H
#define FIBER_H

#include <ucontext.h>

#define FIBER_STACK_SIZE 64 * 1024
#define MAX_FIBERS 100

typedef enum {
    FIBER_READY,
    FIBER_RUNNING,
    FIBER_BLOCKED,
    FIBER_TERMINATED
} FiberState;

typedef struct Fiber {
    int id;
    FiberState state;

    ucontext_t context;

    void (*function)(void);
    void *stack;

    int priority;
} Fiber;

/* Fiber management */
void fiber_init(void);

int fiber_create(void (*function)(void), int priority);

void fiber_yield(void);

void fiber_exit(void);

void fiber_join(int fiber_id);

/* Scheduler */
void scheduler_run(void);

void scheduler_set_policy(int policy);

/* Utility */
int fiber_get_current_id(void);

void fiber_switch_context(Fiber *current, Fiber *next);

/* Ready queue */
void queue_init(void);
int queue_push(Fiber *fiber);
Fiber *queue_pop(void);
int queue_empty(void);
int queue_size(void);

/* Fiber Mutex */
typedef struct {
    int locked;
    int owner;
} FiberMutex;

void fiber_mutex_init(FiberMutex *mutex);
void fiber_mutex_lock(FiberMutex *mutex);
void fiber_mutex_unlock(FiberMutex *mutex);

void scheduler_run(void);
void scheduler_start(void);

#endif
