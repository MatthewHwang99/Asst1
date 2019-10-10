all: memgrind

memgrind: memgrind.c mymalloc.o
	gcc -std=c99 -g memgrind.c -o memgrind mymalloc.o
mymalloc.o: mymalloc.c mymalloc.h
	gcc -std=c99 -g -c mymalloc.c -o mymalloc.o
clean:
	rm -rf memgrind
	rm -rf mymalloc.o
