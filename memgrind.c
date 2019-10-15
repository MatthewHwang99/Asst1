#include "mymalloc.h"

int main(int argc, char** argv){
	int i; int j;
	
	char* p = (char*)malloc(1);
	free(p);
	
	//A: malloc() 1 byte and immediately free it - do this 150 times
	/*for(i = 0; i<150; i++){
		p = (char*)malloc(1);
		free(p);
	}*/
	
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
	}*/
	
	/*C: Randomly choose between a 1 byte malloc or freeing a 1 byte pointer
			>do this until you have allocated 50 times
		Keep track of each operation so that you eventually malloc 50 bytes, in total
			>if you have already allocated 50 times, disregard the random and just free on each iteration
		Keep track of each operation so that you eventually free all pointer
			>don't allow a free if you have no pointers to free*/
	/*void* arr[50];
	for(i=0;i<50;i++){
		
	
	}*/
	
	
	/*D: Randomly choose between a randomly-sized malloc of free ing a pointer - do this many times
		- Keep track of each malloc so that all mallocs do not exceed your total memory capacity
		- Keep track of each operation so that you eventually malloc 50 times
		- Keep track of each operation so that you eventually free() all pointers
		- Choose a random allocated size between 1 and 64 bytes*/
		
	
	/*E,F: Two more works loads of your choosing
		- Both described in testplan.txt*/
		
				

	return 0;
}
