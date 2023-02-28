#ifndef ALLOC_LL_HEADER
#define ALLOC_LL_HEADER

#include "linked_list.h"

#define SIZE_HEAP 1024

void* heap;

double_linked_list* buffer_tracker;

#define BUFF_FREE 0
#define BUFF_FILLED 1

void init_heap(void);
void free_heap(void);

// allocate a pointer of size size
void* heap_malloc(unsigned int size);
// free a pointer in the heap
void heap_free(void *ptr);

double_linked_list* (*strategy)(unsigned int size);
void set_strategy(double_linked_list* (*strat)(unsigned int size));
double_linked_list* first_fit(unsigned int size);

#endif