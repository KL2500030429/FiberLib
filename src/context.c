#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "../include/fiber.h"

/*
 * Switch execution from the current fiber
 * to another fiber.
 */
void fiber_switch_context(Fiber *current, Fiber *next)
{
    if (current == next) {
        return;
    }

    if (swapcontext(&current->context, &next->context) == -1) {
        perror("swapcontext");
        exit(EXIT_FAILURE);
    }
}
