TARGETS = randomselect

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

randomselect: randomselect.o randomizer.o pcg_basic.o

pcg_basic.o: pcg_basic.c pcg_basic.h
randomizer.o: randomizer.c randomizer.h
randomselect.o: randomselect.c randomizer.h