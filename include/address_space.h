#ifndef ADDRESS_SPACE_H
#define ADDRESS_SPACE_H

#define MAX_ADDRESS_SPACES 100

typedef struct {
    int id;
    int owner_job;
    unsigned long code_start;
    unsigned long data_start;
    unsigned long heap_start;
    unsigned long stack_start;
    unsigned long heap_size;
    unsigned long stack_size;
} AddressSpace;

void address_space_init(void);

int address_space_create(int job_id);

void address_space_destroy(int space_id);

void address_space_print(int space_id);

void address_space_print_all(void);

#endif
