#include <stdio.h>
#include "../include/page_replacement.h"

static int find_page(int frames[], int frame_count, int page)
{
    for (int i = 0; i < frame_count; i++) {
        if (frames[i] == page) {
            return i;
        }
    }

    return -1;
}

void fifo_page_replacement(
    int pages[],
    int n,
    int frames
)
{
    int frame[frames];

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    int pointer = 0;
    int page_faults = 0;

    printf("\n========================================\n");
    printf("       FIFO PAGE REPLACEMENT\n");
    printf("========================================\n");

    for (int i = 0; i < n; i++) {

        printf("\nPage %d: ", pages[i]);

        if (find_page(frame, frames, pages[i]) != -1) {
            printf("HIT | Frames: ");
        } else {
            frame[pointer] = pages[i];
            pointer = (pointer + 1) % frames;
            page_faults++;

            printf("PAGE FAULT | Frames: ");
        }

        for (int j = 0; j < frames; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }

        printf("\n");
    }

    printf("\nTotal FIFO Page Faults: %d\n", page_faults);
    printf("========================================\n");
}

static int find_optimal_position(
    int pages[],
    int n,
    int current,
    int frame_page
)
{
    for (int i = current + 1; i < n; i++) {
        if (pages[i] == frame_page) {
            return i;
        }
    }

    return n + 1;
}

void optimal_page_replacement(
    int pages[],
    int n,
    int frames
)
{
    int frame[frames];

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    int page_faults = 0;

    printf("\n========================================\n");
    printf("      OPTIMAL PAGE REPLACEMENT\n");
    printf("========================================\n");

    for (int i = 0; i < n; i++) {

        printf("\nPage %d: ", pages[i]);

        if (find_page(frame, frames, pages[i]) != -1) {
            printf("HIT | Frames: ");
        } else {

            page_faults++;

            int replace_index = -1;

            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    replace_index = j;
                    break;
                }
            }

            if (replace_index == -1) {

                int farthest = -1;

                for (int j = 0; j < frames; j++) {

                    int next_use =
                        find_optimal_position(
                            pages,
                            n,
                            i,
                            frame[j]
                        );

                    if (next_use > farthest) {
                        farthest = next_use;
                        replace_index = j;
                    }
                }
            }

            frame[replace_index] = pages[i];

            printf("PAGE FAULT | Frames: ");
        }

        for (int j = 0; j < frames; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }

        printf("\n");
    }

    printf("\nTotal Optimal Page Faults: %d\n", page_faults);
    printf("========================================\n");
}
