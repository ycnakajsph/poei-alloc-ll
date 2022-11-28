#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../alloc_ll.h"

void test_init_heap(){

	init_heap();

	CU_ASSERT(buffer_tracker->size == SIZE_HEAP);
	CU_ASSERT(buffer_tracker->filled == BUFF_FREE);
	CU_ASSERT(buffer_tracker->next == NULL);
	CU_ASSERT(buffer_tracker->prev == NULL);

	free_heap();
}

void test_first_fit_init(){

	init_heap();

	double_linked_list* track = first_fit(12);

	CU_ASSERT(track == buffer_tracker);

	free_heap();
}

void test_heap_malloc_init(){

	init_heap();

	unsigned int ptr_size = 12;
	char* ptr = (char*) heap_malloc(ptr_size*sizeof(char));
	double_linked_list* track;

	CU_ASSERT(ptr == heap);

	track = buffer_tracker;

	CU_ASSERT(track->ptr == ptr);
	CU_ASSERT(track->size == ptr_size);

	track = track->next;
	CU_ASSERT(track->ptr == ptr+ptr_size);
	CU_ASSERT(track->size == SIZE_HEAP - ptr_size);
	CU_ASSERT(track->filled == BUFF_FREE);

	free_heap();
}

void test_heap_malloc_full_size(){

	init_heap();

	unsigned int ptr_size = SIZE_HEAP;
	char* ptr = (char*) heap_malloc(ptr_size*sizeof(char));
	double_linked_list* track;

	CU_ASSERT(ptr == heap);

	track = buffer_tracker;

	CU_ASSERT(track->ptr == ptr);
	CU_ASSERT(track->size == ptr_size);
	CU_ASSERT(track->next == NULL);

	free_heap();
}

void test_first_fit_malloc(){

	init_heap();

	unsigned int ptr0_size = 12;
	unsigned int ptr1_size = 13;
	char* ptr0 = (char*) heap_malloc(ptr0_size*sizeof(char));

	double_linked_list* track = first_fit(ptr1_size);

	CU_ASSERT(track->ptr == ptr0+ptr0_size);

	free_heap();
}

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

int main()
{
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if (
		NULL == CU_add_test(pSuite, "test_init_heap()", test_init_heap) ||
		NULL == CU_add_test(pSuite, "test_first_fit_init()", test_first_fit_init)||
		NULL == CU_add_test(pSuite, "test_heap_malloc_init()", test_heap_malloc_init)||
		NULL == CU_add_test(pSuite, "test_heap_malloc_full_size()", test_heap_malloc_full_size)||
		NULL == CU_add_test(pSuite, "test_first_fit_malloc()", test_first_fit_malloc)
	)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
