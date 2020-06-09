CFLAGS = -Wall -pedantic
TARGETS = bst

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

bst: bst.o string_format.o

bst.o: bst.c bst.h string_format.h
string_format.o: string_format.c string_format.h