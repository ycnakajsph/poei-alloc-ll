CC ?= gcc
CFLAGS += -Wall --pedantic -Werror
DEBUG_FLAGS += -g
CFILES = alloc_ll.c
LOCAL_LIB=/home/yann/projects/poe/alloc_ll/linkedlist
LOCAL_INC=/home/yann/projects/poe/alloc_ll/linkedlist

all:
	$(CC) $(LDFLAGS) -L$(LOCAL_LIB) -I$(LOCAL_INC) -o alloc_ll $(CFLAGS) $(CFILES) main.c -llinkedlist

test:
	$(CC) $(LDFLAGS) -L$(LOCAL_LIB) -I$(LOCAL_INC) -g -o alloc_ll_tests $(CFLAGS) tests/test_main.c $(CFILES) -lcunit -llinkedlist

clean:
	rm -f *.o alloc_ll_tests alloc_ll *.so
