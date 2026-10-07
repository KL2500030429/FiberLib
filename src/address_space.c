#include <stdio.h>

#include "../include/address_space.h"

static AddressSpace spaces[MAX_ADDRESS_SPACES];

static int space_count = 0;


/*
 * Initialize address-space manager.
 */
void address_space_init(void)
{
    space_count = 0;

    for (int i = 0; i < MAX_ADDRESS_SPACES; i++) {
        spaces[i].id = -1;
        spaces[i].owner_job = -1;
    }
}


/*
 * Create an address space for a job.
 */
int address_space_create(int job_id)
{
    if (space_count >= MAX_ADDRESS_SPACES) {
        printf("Error: Maximum address spaces reached.\n");
        return -1;
    }

    int id = space_count;

    spaces[id].id = id;
    spaces[id].owner_job = job_id;

    /*
     * Simulated virtual addresses.
     */
    spaces[id].code_start  = 0x00400000;
    spaces[id].data_start  = 0x00600000;
    spaces[id].heap_start  = 0x01000000;
    spaces[id].stack_start = 0x7FFFFFFF;

    spaces[id].heap_size = 1024 * 1024;
    spaces[id].stack_size = 64 * 1024;

    space_count++;

    printf(
        "Address Space %d created for Job %d.\n",
        id,
        job_id
    );

    return id;
}


/*
 * Destroy an address space.
 */
void address_space_destroy(int space_id)
{
    if (space_id < 0 || space_id >= space_count) {
        printf("Invalid address space ID.\n");
        return;
    }

    printf(
        "Address Space %d destroyed.\n",
        space_id
    );

    spaces[space_id].id = -1;
    spaces[space_id].owner_job = -1;
}


/*
 * Print one address space.
 */
void address_space_print(int space_id)
{
    if (space_id < 0 || space_id >= space_count) {
        printf("Invalid address space ID.\n");
        return;
    }

    AddressSpace *space = &spaces[space_id];

    printf("\n========================================\n");
    printf("        ADDRESS SPACE %d\n", space->id);
    printf("========================================\n");

    printf("Owner Job     : %d\n", space->owner_job);

    printf("Code Start    : 0x%08lX\n",
           space->code_start);

    printf("Data Start    : 0x%08lX\n",
           space->data_start);

    printf("Heap Start    : 0x%08lX\n",
           space->heap_start);

    printf("Heap Size     : %lu bytes\n",
           space->heap_size);

    printf("Stack Start   : 0x%08lX\n",
           space->stack_start);

    printf("Stack Size    : %lu bytes\n",
           space->stack_size);

    printf("========================================\n");
}


/*
 * Print all address spaces.
 */
void address_space_print_all(void)
{
    printf("\n========================================\n");
    printf("        ADDRESS SPACE TABLE\n");
    printf("========================================\n");

    printf(
        "%-8s %-12s %-15s %-15s\n",
        "ID",
        "JOB",
        "HEAP SIZE",
        "STACK SIZE"
    );

    printf("----------------------------------------\n");

    for (int i = 0; i < space_count; i++) {

        if (spaces[i].id != -1) {

            printf(
                "%-8d %-12d %-15lu %-15lu\n",
                spaces[i].id,
                spaces[i].owner_job,
                spaces[i].heap_size,
                spaces[i].stack_size
            );
        }
    }

    printf("========================================\n");
}
