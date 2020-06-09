CFLAGS = -Wall -pedantic
TARGETS = graph

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

graph: graph.o binary_heap.o binary_heap_2.o disjoint_set.o

graph.o: graph.c graph.h binary_heap.h graph_struct.h binary_heap_2.h graph_struct_2.h disjoint_set.h
binary_heap.o: binary_heap.c binary_heap.h graph_struct.h
binary_heap_2.o: binary_heap_2.c binary_heap_2.h graph_struct_2.h
disjoint_set.o: disjoint_set.c disjoint_set.h