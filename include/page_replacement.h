#ifndef PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_H

void fifo_page_replacement(
    int pages[],
    int n,
    int frames
);

void optimal_page_replacement(
    int pages[],
    int n,
    int frames
);

#endif
