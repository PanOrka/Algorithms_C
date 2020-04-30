TARGETS = select
CC = gcc # flag for gcc
LOADLIBES = -lm # flag for libraries

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

select: select.o linear_search.o select_algorithm.o displayer.o randomizer.o pcg_basic.o

pcg_basic.o: pcg_basic.c pcg_basic.h
randomizer.o: randomizer.c randomizer.h
select_algorithm.o: select_algorithm.c select_algorithm.h displayer.h
linear_search.o: linear_search.c linear_search.h displayer.h
displayer.o: displayer.c displayer.h
select.o: select.c randomizer.h linear_search.h select_algorithm.h displayer.h