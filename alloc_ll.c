#include <stdio.h>
#include <stdlib.h>
#include "alloc_ll.h"
#include "linked_list.h"

void set_strategy(double_linked_list* (*strat)(unsigned int size)){
	strategy = strat;
}

void init_heap(void){
	heap = malloc(SIZE_HEAP*sizeof(void*));
	if (heap == NULL){
		printf("malloc error\n");
		exit(1);
	}

	buffer_tracker = d_ll_get_new_elem(heap,SIZE_HEAP,BUFF_FREE); // setting first buffer free

	set_strategy(&first_fit);
}

void free_heap(void){
	free(heap);
	d_ll_free(buffer_tracker);
}


double_linked_list* first_fit(unsigned int size){

	double_linked_list* track = buffer_tracker;

	if (track->size >= size && track->filled == BUFF_FREE){
		return track;
	}

	while (track != NULL) {
		if(track->size >= size && track->filled == BUFF_FREE){
			return track;
		}
		track = track->next;
	}
	return NULL;
}

void* heap_malloc(unsigned int size){

	double_linked_list* track = strategy(size);
	double_linked_list* new_buff_free;
	unsigned int leftover;

	if (track == NULL){
		return NULL;
	}

	track->filled = BUFF_FILLED;

	leftover = track->size - size;

	if (leftover > 1){
		track->size = size;
		new_buff_free = d_ll_get_new_elem((char*)track->ptr+size, leftover, BUFF_FREE);
		track->next = new_buff_free;
		new_buff_free->prev = track;
	}

	return track->ptr;
}