CFLAGS = -Wall -pedantic
TARGETS = test

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

test: test.o binary_heap.o

test.o: test.c binary_heap.h
binary_heap.o: binary_heap.c binary_heap.h