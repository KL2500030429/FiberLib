#include <stdio.h>
#include "../include/memory_manager.h"

int main(void)
{
    printf("\n========================================\n");
    printf("      FiberLib Dynamic Memory Demo\n");
    printf("========================================\n\n");

    memory_manager_init();

    memory_print_status();

    printf("\n--- Allocating Memory ---\n");

    void *ptr1 = memory_alloc(100);
    void *ptr2 = memory_alloc(200);
    void *ptr3 = memory_alloc(300);

    (void)ptr1;
    (void)ptr3;

    memory_print_status();

    printf("\n--- Freeing Second Block ---\n");

    memory_free(ptr2);

    memory_print_status();

    printf("\nDynamic Memory Demo Completed.\n");

    return 0;
}
