CFLAGS = -Wall -pedantic
TARGETS = run

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

run: run.o rw_lw.o mst_euler.o

run.o: run.c ./rw_lw/graph.h ./MST_euler_cycle/graph.h
rw_lw.o:
	cd ./rw_lw && make && make clean
mst_euler.o:
	cd ./MST_euler_cycle && make && make clean