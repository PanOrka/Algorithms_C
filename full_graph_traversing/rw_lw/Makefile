CFLAGS = -Wall -pedantic
TARGETS = rw_lw

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

rw_lw: graph.o pcg_basic.o
	ld -r graph.o pcg_basic.o -o ../rw_lw.o

graph.o: graph.c graph.h pcg_basic.h
pcg_basic.o: pcg_basic.c pcg_basic.h