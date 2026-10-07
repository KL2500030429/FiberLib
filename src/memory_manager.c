#include <stdio.h>
#include "../include/memory_manager.h"

typedef struct MemoryBlock {
    unsigned int size;
    int free;
    struct MemoryBlock *next;
} MemoryBlock;

static unsigned char memory_pool[MEMORY_POOL_SIZE];
static MemoryBlock *free_list = NULL;

void memory_manager_init(void)
{
    free_list = (MemoryBlock *)memory_pool;

    free_list->size =
        MEMORY_POOL_SIZE - sizeof(MemoryBlock);

    free_list->free = 1;
    free_list->next = NULL;

    printf("Memory Manager initialized.\n");
}

void *memory_alloc(unsigned int size)
{
    if (size == 0 || free_list == NULL) {
        return NULL;
    }

    MemoryBlock *current = free_list;

    while (current != NULL) {

        if (current->free && current->size >= size) {

            /*
             * Split the block if enough space remains
             * for another memory block.
             */
            if (current->size >=
                size + sizeof(MemoryBlock) + 1) {

                MemoryBlock *new_block =
                    (MemoryBlock *)(
                        (unsigned char *)(current + 1)
                        + size
                    );

                new_block->size =
                    current->size -
                    size -
                    sizeof(MemoryBlock);

                new_block->free = 1;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }

            current->free = 0;

            printf(
                "Allocated %u bytes.\n",
                size
            );

            return (void *)(current + 1);
        }

        current = current->next;
    }

    printf("Memory allocation failed.\n");

    return NULL;
}

void memory_free(void *ptr)
{
    if (ptr == NULL) {
        return;
    }

    MemoryBlock *block =
        ((MemoryBlock *)ptr) - 1;

    block->free = 1;

    printf(
        "Memory block of %u bytes freed.\n",
        block->size
    );

    /*
     * Merge adjacent free blocks.
     */
    MemoryBlock *current = free_list;

    while (current != NULL &&
           current->next != NULL) {

        if (current->free &&
            current->next->free) {

            current->size +=
                sizeof(MemoryBlock) +
                current->next->size;

            current->next =
                current->next->next;
        } else {
            current = current->next;
        }
    }
}

void memory_print_status(void)
{
    MemoryBlock *current = free_list;

    printf("\n========================================\n");
    printf("        MEMORY MANAGER STATUS\n");
    printf("========================================\n");

    int block_id = 0;

    while (current != NULL) {

        printf(
            "Block %d : Size = %u bytes | %s\n",
            block_id,
            current->size,
            current->free ? "FREE" : "ALLOCATED"
        );

        current = current->next;
        block_id++;
    }

    printf("========================================\n");
}
