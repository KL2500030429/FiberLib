#include <stdio.h>
#include <string.h>

#include "../include/job_control.h"

static Job jobs[MAX_JOBS];

static int job_count = 0;


/*
 * Initialize job control.
 */
void job_control_init(void)
{
    job_count = 0;

    for (int i = 0; i < MAX_JOBS; i++) {
        jobs[i].id = -1;
        jobs[i].state = JOB_TERMINATED;
        jobs[i].name[0] = '\0';
    }
}


/*
 * Create a new job.
 */
int job_create(const char *name)
{
    if (job_count >= MAX_JOBS) {
        printf("Error: Maximum number of jobs reached.\n");
        return -1;
    }

    if (name == NULL) {
        return -1;
    }

    int id = job_count;

    jobs[id].id = id;
    jobs[id].state = JOB_READY;

    strncpy(
        jobs[id].name,
        name,
        sizeof(jobs[id].name) - 1
    );

    jobs[id].name[sizeof(jobs[id].name) - 1] = '\0';

    job_count++;

    printf(
        "Job %d created: %s\n",
        id,
        jobs[id].name
    );

    return id;
}


/*
 * Run a job.
 */
void job_run(int job_id)
{
    if (job_id < 0 || job_id >= job_count) {
        printf("Invalid job ID.\n");
        return;
    }

    if (jobs[job_id].state == JOB_READY ||
        jobs[job_id].state == JOB_SUSPENDED) {

        jobs[job_id].state = JOB_RUNNING;

        printf(
            "Job %d is now RUNNING.\n",
            job_id
        );
    }
}


/*
 * Suspend a running job.
 */
void job_suspend(int job_id)
{
    if (job_id < 0 || job_id >= job_count) {
        printf("Invalid job ID.\n");
        return;
    }

    if (jobs[job_id].state == JOB_RUNNING) {

        jobs[job_id].state = JOB_SUSPENDED;

        printf(
            "Job %d is now SUSPENDED.\n",
            job_id
        );
    }
}


/*
 * Resume a suspended job.
 */
void job_resume(int job_id)
{
    if (job_id < 0 || job_id >= job_count) {
        printf("Invalid job ID.\n");
        return;
    }

    if (jobs[job_id].state == JOB_SUSPENDED) {

        jobs[job_id].state = JOB_RUNNING;

        printf(
            "Job %d RESUMED.\n",
            job_id
        );
    }
}


/*
 * Terminate a job.
 */
void job_terminate(int job_id)
{
    if (job_id < 0 || job_id >= job_count) {
        printf("Invalid job ID.\n");
        return;
    }

    if (jobs[job_id].state != JOB_TERMINATED) {

        jobs[job_id].state = JOB_TERMINATED;

        printf(
            "Job %d TERMINATED.\n",
            job_id
        );
    }
}


/*
 * Convert state to readable text.
 */
static const char *job_state_name(JobState state)
{
    switch (state) {

        case JOB_READY:
            return "READY";

        case JOB_RUNNING:
            return "RUNNING";

        case JOB_SUSPENDED:
            return "SUSPENDED";

        case JOB_TERMINATED:
            return "TERMINATED";

        default:
            return "UNKNOWN";
    }
}


/*
 * Display all jobs.
 */
void job_print_all(void)
{
    printf("\n========================================\n");
    printf("             JOB TABLE\n");
    printf("========================================\n");

    printf(
        "%-8s %-20s %-15s\n",
        "ID",
        "NAME",
        "STATE"
    );

    printf("----------------------------------------\n");

    for (int i = 0; i < job_count; i++) {

        printf(
            "%-8d %-20s %-15s\n",
            jobs[i].id,
            jobs[i].name,
            job_state_name(jobs[i].state)
        );
    }

    printf("========================================\n");
}
