CFLAGS = -Wall -pedantic
TARGETS = rbt

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

rbt: rbt.o rbt_functions.o string_format.o

rbt.o: rbt.c rbt_functions.h rbt.h string_format.h
rbt_functions.o: rbt_functions.c rbt_functions.h rbt.h
string_format.o: string_format.c string_format.h