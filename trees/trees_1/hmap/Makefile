CFLAGS = -Wall -pedantic
TARGETS = hmap

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

hmap: hmap.o rbt.o rbt_functions.o string_format.o hash_func.o twlist.o

hmap.o: hmap.c hmap.h rbt.h twlist.h string_format.h hash_func.h
rbt.o: rbt.c rbt_functions.h rbt.h string_format.h
rbt_functions.o: rbt_functions.c rbt_functions.h rbt.h
string_format.o: string_format.c string_format.h
hash_func.o: hash_func.c hash_func.h
twlist.o: twlist.c twlist.h