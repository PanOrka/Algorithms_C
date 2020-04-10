TARGETS = randomselect

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

randomselect: randomselect.o randomizer.o median.o pcg_basic.o

pcg_basic.o: pcg_basic.c pcg_basic.h
randomizer.o: randomizer.c randomizer.h
median.o: median.c median.h
randomselect.o: randomselect.c median.h randomizer.h