#include <stdio.h>
#include "../include/fiber.h"

#define QUEUE_SIZE MAX_FIBERS

static Fiber *ready_queue[QUEUE_SIZE];

static int front = 0;
static int rear = 0;
static int count = 0;

/* Initialize the ready queue */
void queue_init(void)
{
    front = 0;
    rear = 0;
    count = 0;
}

/* Add a fiber to the ready queue */
int queue_push(Fiber *fiber)
{
    if (count >= QUEUE_SIZE) {
        return -1;
    }

    ready_queue[rear] = fiber;
    rear = (rear + 1) % QUEUE_SIZE;
    count++;

    return 0;
}

/* Remove a fiber from the ready queue */
Fiber *queue_pop(void)
{
    Fiber *fiber;

    if (count == 0) {
        return NULL;
    }

    fiber = ready_queue[front];

    front = (front + 1) % QUEUE_SIZE;
    count--;

    return fiber;
}

/* Check whether the queue is empty */
int queue_empty(void)
{
    return count == 0;
}

/* Return number of fibers in queue */
int queue_size(void)
{
    return count;
}
