CC ?= gcc
CFLAGS += -Wall --pedantic -Werror
DEBUG_FLAGS += -g
CFILES = alloc_ll.c
all:
	$(CC) $(LDFLAGS) -o alloc_ll $(CFLAGS) $(CFILES) main.c

test:
	$(CC) $(LDFLAGS)  -o alloc_ll_tests $(CFLAGS) tests/test_main.c $(CFILES) -lcunit

clean:
	rm -f *.o alloc_ll_tests alloc_ll *.so
