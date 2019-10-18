#include "mymalloc.h"

int main(int argc, char** argv){
	int i; int j;
      	//printf("sizeof:char %d\n", sizeof(char));
	//printf("sizeof:short %d\n", sizeof(short));
	//printf("sizeof:metadata %d\n", sizeof(struct metadata));
	char* p;// = (char*)malloc(10);
	//free(p);
	
	
	
	//A: malloc() 1 byte and immediately free it - do this 150 times
	/*	for(i = 0; i<150; i++){
		p = (char*)malloc(1);
		//printf("malloc(): %d\n", i);
		free(p);
		//printf("free(): %d\n", i);
	}
	*/
	/*B: malloc() 1 byte, store the pointer in an array - do this 150 times.
		Once you've malloced 50 byte chunks, then free the 50 1 byte pointers one by one*/
	/*void* arr[50];
	for(j = 0; j<3; j++){
		for(i = 0; i<50; i++){
			p = (char*)malloc(1);
			arr[i]=p;
		}
		for(i = 0; i<50; i++){
			free(arr[i]);
		}
	}
	*/
	/*C: Randomly choose between a 1 byte malloc or freeing a 1 byte pointer
			>do this until you have allocated 50 times
		Keep track of each operation so that you eventually malloc 50 bytes, in total
			>if you have already allocated 50 times, disregard the random and just free on each iteration
		Keep track of each operation so that you eventually free all pointer
			>don't allow a free if you have no pointers to free*/
	/*
	void* arr[50];
        int allocate = 0, pos = 0, temp;
	srand(time(NULL));
	while(allocate < 50){
	  temp = (rand() % 2);
	  if(temp == 1){
	    p = (char*)malloc(1);
	    arr[pos] = p;
	    allocate++;
	    pos++;
	  }else{
	    if(allocate > 0 && pos > 0){
	      free(arr[pos]);
	      pos--;
	    printf("pos %d\n", pos);
	    }
	  }
	}
	for(i = 0; i < pos; i++){
	  printf("free end\n");
	  free(arr[i]);
	}
*/
	
	/*D: Randomly choose between a randomly-sized malloc or freeing a pointer - do this many times
		- Keep track of each malloc so that all mallocs do not exceed your total memory capacity
		- Keep track of each operation so that you eventually malloc 50 times
		- Keep track of each operation so that you eventually free() all pointers
		- Choose a random allocated size between 1 and 64 bytes*/
	/*	
	void* array[50];
        int counter = 0, arrpos = 0, tempor, size;
	srand(time(NULL));
	while(counter < 50){
	  tempor = (rand() % 2);
	  if(tempor == 1){
	    printf("counter-> %d\n", counter);
	    size = (rand() % 65);
	    while(size == 0){
	      size = (rand() % 65);	      
	    }
	    p = (char*)malloc(size);
	    array[arrpos] = p;
	    counter++;
	    arrpos++;
	  }else{
	    if(counter > 0 && arrpos > 0){
	      free(array[arrpos]);
	      arrpos--;
	    printf("pos %d\n", arrpos);
	    }
	  }
	}
	for(i = 0; i < arrpos; i++){
	  printf("free end\n");
	  free(array[i]);
	}		
	*/
	/*E,F: Two more works loads of your choosing
		- Both described in testplan.txt*/

	//E: malloc three times of random times, free the two outside blocks of memory, when the middle block is freed all three blocks
	//are expected to be merged into one big block
	/*
	char* x, *y, *z;
	int size = (4096 - sizeof(struct metadata)*3) / 3;
	x = (char*)malloc(size);
	y = (char*)malloc(size);
	z = (char*)malloc(size);
	free(x);
	free(z);
	free(y);
	*/

	//F: malloc until the block is full, then free all pointers

		
				

	return 0;
}
