CFLAGS = -Wall -pedantic
TARGETS = pre_make test
SEC_TARGETS = ./binary_search_tree/bst ./red_black_tree/rbt ./hmap/hmap

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)
	rm -f ./binary_search_tree/*.o $(SEC_TARGETS)
	rm -f ./red_black_tree/*.o
	rm -f ./hmap/*.o

pre_make:
	+$(MAKE) -C ./binary_search_tree/
	+$(MAKE) -C ./red_black_tree/
	+$(MAKE) -C ./hmap/

test: test.c