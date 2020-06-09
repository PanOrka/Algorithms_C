CFLAGS = -Wall -pedantic
TARGETS = graph

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

graph: graph.o binary_heap.o

graph.o: graph.c graph.h binary_heap.h graph_struct.h
binary_heap.o: binary_heap.c binary_heap.h graph_struct.h