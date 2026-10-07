#include <stdio.h>
#include "../include/page_replacement.h"

int main(void)
{
    int pages[] = {
        7, 0, 1, 2, 0, 3, 0, 4,
        2, 3, 0, 3, 2
    };

    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    printf("\n========================================\n");
    printf("    FiberLib Page Replacement Demo\n");
    printf("========================================\n");

    printf("\nReference String:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }

    printf("\nFrames: %d\n", frames);

    fifo_page_replacement(
        pages,
        n,
        frames
    );

    optimal_page_replacement(
        pages,
        n,
        frames
    );

    printf("\nPage Replacement Demo Completed.\n");

    return 0;
}
