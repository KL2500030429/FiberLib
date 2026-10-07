#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#define MEMORY_POOL_SIZE 1024 * 1024

void memory_manager_init(void);
void *memory_alloc(unsigned int size);
void memory_free(void *ptr);
void memory_print_status(void);

#endif
