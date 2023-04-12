CC ?= gcc
CFLAGS += -Wall --pedantic -Werror
DEBUG_FLAGS += -g -O0
CFILES = alloc_ll.c

all:
	$(CC) $(LDFLAGS) -o alloc_ll $(CFLAGS) $(CFILES) main.c -llinkedlist

valgrind:
	$(CC) $(LDFLAGS) $(DEBUG_FLAGS) -o valgrind_alloc_ll $(CFLAGS) $(CFILES) main.c -llinkedlist

test:
	$(CC) $(LDFLAGS) -g -o alloc_ll_tests $(CFLAGS) tests/test_main.c $(CFILES) -lcunit -llinkedlist

clean:
	rm -f *.o alloc_ll_tests alloc_ll *.so
