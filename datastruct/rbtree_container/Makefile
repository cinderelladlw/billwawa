debug = -g

target = test benchmark stlmap_benchmark

all: $(target)

test: test.o rbtree.o rbtree_container.o
	gcc $(debug) -Wall -o test test.o rbtree.o rbtree_container.o

benchmark: benchmark.o rbtree.o rbtree_container.o
	gcc $(debug) -Wall -o benchmark benchmark.o rbtree.o rbtree_container.o

stlmap_benchmark: STL_map_benchmark.cpp
	g++ $(debug) -Wall -o stlmap_benchmark STL_map_benchmark.cpp

test.o: test.c rbtree_container.h rbtree.h
	gcc $(debug) -c -Wall -o test.o test.c

benchmark.o: benchmark.c rbtree_container.h rbtree.h
	gcc $(debug) -c -Wall -o benchmark.o benchmark.c

rbtree_container.o: rbtree_container.c rbtree_container.h rbtree.h
	gcc $(debug) -c -Wall -o rbtree_container.o rbtree_container.c

rbtree.o: rbtree.c rbtree.h
	gcc $(debug) -c -Wall -o rbtree.o rbtree.c

.PHONY: clean
clean:
	rm *.o $(target)

.PHONY: co
co:
	rm *.o
