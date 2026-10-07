#include <stdio.h>

#include "../include/job_control.h"

int main(void)
{
    printf("\n========================================\n");
    printf("        FiberLib Job Control Demo\n");
    printf("========================================\n\n");

    /*
     * Initialize job control.
     */
    job_control_init();

    /*
     * Create jobs.
     */
    int job1 = job_create("Compiler");
    int job2 = job_create("Data Processing");
    int job3 = job_create("Background Task");

    printf("\nInitial Job Table:\n");

    job_print_all();

    /*
     * Run first job.
     */
    printf("\n--- Running Job 1 ---\n");

    job_run(job1);

    /*
     * Suspend first job.
     */
    printf("\n--- Suspending Job 1 ---\n");

    job_suspend(job1);

    /*
     * Run second job.
     */
    printf("\n--- Running Job 2 ---\n");

    job_run(job2);

    /*
     * Resume first job.
     */
    printf("\n--- Resuming Job 1 ---\n");

    job_resume(job1);

    /*
     * Terminate second job.
     */
    printf("\n--- Terminating Job 2 ---\n");

    job_terminate(job2);

    /*
     * Terminate third job.
     */
    printf("\n--- Terminating Job 3 ---\n");

    job_terminate(job3);

    /*
     * Final job table.
     */
    printf("\nFinal Job Table:\n");

    job_print_all();

    printf("\nJob Control Demo Completed.\n");

    return 0;
}
