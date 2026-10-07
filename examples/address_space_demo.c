#include <stdio.h>

#include "../include/address_space.h"

int main(void)
{
    printf("\n========================================\n");
    printf("      FiberLib Address Space Demo\n");
    printf("========================================\n\n");

    address_space_init();

    /*
     * Create address spaces for jobs.
     */
    int space1 = address_space_create(0);
    int space2 = address_space_create(1);
    int space3 = address_space_create(2);

    /*
     * Display individual address spaces.
     */
    address_space_print(space1);
    address_space_print(space2);
    address_space_print(space3);

    /*
     * Display complete table.
     */
    address_space_print_all();

    /*
     * Destroy one address space.
     */
    printf("\n--- Destroying Address Space 1 ---\n");

    address_space_destroy(space1);

    address_space_print_all();

    printf("\nAddress Space Demo Completed.\n");

    return 0;
}
