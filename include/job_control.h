#ifndef JOB_CONTROL_H
#define JOB_CONTROL_H

#define MAX_JOBS 100

typedef enum {
    JOB_READY,
    JOB_RUNNING,
    JOB_SUSPENDED,
    JOB_TERMINATED
} JobState;

typedef struct {
    int id;
    JobState state;
    char name[50];
} Job;

void job_control_init(void);

int job_create(const char *name);

void job_run(int job_id);

void job_suspend(int job_id);

void job_resume(int job_id);

void job_terminate(int job_id);

void job_print_all(void);

#endif
