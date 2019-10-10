#ifndef mymalloc.h
#define mymalloc.h

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<math.h>

//macros to replace all calls to malloc(x) with calls to mymalloc(x)
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
//macros to replace all calls to free(x) with myfree(x)
#define free(x) myfree(x, __FILE__, __LINE__)

//function signature for mymalloc(x) code
void* mymalloc(int, __FILE__, __LINE__);

//function signature for myfree(x) code
void* myfree(int, __FILE__, __LINE__);

//metadata struct definition
struct md{
	char isFree; //use a char to store whether the block of memory is "free" | '0' = Not free, '1' = Free
	short size; //use a short to store the size of the block of memory since it is smaller than int
	struct md *next; //pointer to the next metadata entry
}

//definition for a static array of size 4096 to allocate from
static char myblock[4096];

#endif
