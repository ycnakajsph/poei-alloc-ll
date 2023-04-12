#include <stdio.h>
#include <string.h>
#include "alloc_ll.h"

int main(void){
	printf("init heap\n");
	init_heap();

	unsigned int ptr0_size = 12;
	unsigned int ptr1_size = 13;
	unsigned int ptr2_size = 14;

	printf("alloc ptr0\n");
	char* ptr0 = (char*) heap_malloc(ptr0_size*sizeof(char));
	printf("alloc ptr1\n");
	char* ptr1 = (char*) heap_malloc(ptr1_size*sizeof(char));
	printf("alloc ptr2\n");
	char* ptr2 = (char*) heap_malloc(ptr2_size*sizeof(char));

	printf("fill up ptrs\n");
	strcpy(ptr0,"dummy0");
	strcpy(ptr1,"dummy1");
	strcpy(ptr2,"dummy2");

	printf("free ptr1\n");
	heap_free(ptr1);
	printf("free ptr2\n");
	heap_free(ptr2);
	printf("free ptr0\n");
	heap_free(ptr0);

	free_heap();

	return 0;
}