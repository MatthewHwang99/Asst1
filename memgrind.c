#include "mymalloc.h"


int main(int argc, char** argv){

	struct timeval start, end;
	unsigned long timeA = 0; //total times of each workload
	unsigned long timeB = 0;
	unsigned long timeC = 0;
	unsigned long timeD = 0;
	unsigned long timeE = 0;
	unsigned long timeF = 0;
		
	char *p;
	
	//A: malloc() 1 byte and immediately free it - do this 150 times
	for(int i = 0; i<100; i++){
		gettimeofday(&start, 0);
		testA();
		gettimeofday(&end, 0);
		
		timeA += (end.tv_sec - start.tv_sec)*1000000.0 + end.tv_usec - start.tv_usec;
	}
	timeA = timeA/100;
	
	/*B: malloc() 1 byte, store the pointer in an array - do this 150 times.
		Once you've malloced 50 byte chunks, then free the 50 1 byte pointers one by one*/
	
	for(int i = 0; i<100; i++){
		gettimeofday(&start, NULL);
		testB();
		gettimeofday(&end, NULL);

		timeB += (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec;
	}
	timeB = timeB/100;
		
	/*C: Randomly choose between a 1 byte malloc or freeing a 1 byte pointer
				>do this until you have allocated 50 times
			Keep track of each operation so that you eventually malloc 50 bytes, in total
				>if you have already allocated 50 times, disregard the random and just free on each iteration
			Keep track of each operation so that you eventually free all pointer
				>don't allow a free if you have no pointers to free*/
	
	for(int i = 0; i<100; i++){
		gettimeofday(&start, 0);
		testC();
		gettimeofday(&end, 0);
		
		timeC += (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec;
	}
	timeC = timeC/100;
							
	/*D: Randomly choose between a randomly-sized malloc or freeing a pointer - do this many times
			- Keep track of each malloc so that all mallocs do not exceed your total memory capacity
			- Keep track of each operation so that you eventually malloc 50 times
			- Keep track of each operation so that you eventually free() all pointers
			- Choose a random allocated size between 1 and 64 bytes*/
	
	for(int i = 0; i<100; i++){
		gettimeofday(&start, 0);
		testD();
		gettimeofday(&end, 0);
		
		timeD += (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec;
	}
	timeD = timeD/100;
			
	//E: malloc three times of random times, free the two outside blocks of memory, when the middle block is freed all three blocks
	//are expected to be merged into one big block	
	
	for(int i = 0; i<100; i++){
		gettimeofday(&start, 0);
		testE();
		gettimeofday(&end, 0);
		
		timeE += (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec;
	}
	timeE = timeE/100;

	//F: malloc until the block is full, then free all pointers
	
	char* pp;
	char arrayz[5000];
	int z = 0;
	do{
	pp = malloc(rand() % 101);
	arrayz[z] = pp;
	z++;
	}while(pp != NULL);
	
	for(; z >= 0; z++){
	free(arrayz[z]);	
	}
	
	
	
	printf("Average run time for testA: %lu microseconds.\n", timeA);
	printf("Average run time for testB: %lu microseconds.\n", timeB);
	printf("Average run time for testC: %lu microseconds.\n", timeC);
	printf("Average run time for testD: %lu microseconds.\n", timeD);
	printf("Average run time for testE: %lu microseconds.\n", timeE);
	//printf("Average run time for testF: %lu microseconds.\n", timeF);



	return 0;
}

void testA(){
	int i;
	for(int i = 0; i<150; i++){
		char* p = (char*)malloc(1);
		//printf("malloc(): %d\n", i);
		free(p);
		//printf("free(): %d\n", i);
		}
	return;
}

void testB(){
	void* arr[50];
	for(int j = 0; j<3; j++){
		for(int i = 0; i<50; i++){
			char* p = (char*)malloc(1);
			arr[i]=p;
		}
		for(int i = 0; i<50; i++){
			free(arr[i]);
		}
	}	
	return;
}

void testC(){
	void* arr[50];
	int allocate = 0, pos = 0, temp;
	srand(time(NULL));
	
	while(allocate < 50){
		temp = (rand() % 2);
		if(temp == 1){
		  	char* p = (char*)malloc(1);
		    arr[pos] = p;
		    allocate++;
		    pos++;
		  }else{
		    if(allocate > 0 && pos > 0){
		      free(arr[pos]);
		      pos--;
		    //printf("pos %d\n", pos);
		    }
		  }
		}
		for(int i = 0; i < pos; i++){
		//  printf("free end\n");
		  free(arr[i]);
		}
	return;
}

void testD(){
		void* array[50];
    	int counter = 0, arrpos = 0, tempor, size;
		srand(time(NULL));
		while(counter < 50){
		  tempor = (rand() % 2);
		  if(tempor == 1){
		    //printf("counter-> %d\n", counter);
		    size = (rand() % 65);
		    while(size == 0){
		      size = (rand() % 65);	      
		    }
		    char* p = (char*)malloc(size);
		    array[arrpos] = p;
		    counter++;
		    arrpos++;
		  }else{
		    if(counter > 0 && arrpos > 0){
		      free(array[arrpos]);
		      arrpos--;
		    //printf("pos %d\n", arrpos);
		    }
		  }
		}
		for(int i = 0; i < arrpos; i++){
		 // printf("free end\n");
		  free(array[i]);
		}		
	return;
}

void testE(){
	char* x, *y, *z;
	int size = (4096 - sizeof(struct metadata)*3) / 3;
	x = (char*)malloc(size);
	y = (char*)malloc(size);
	z = (char*)malloc(size);
	free(x);
	free(z);
	free(y);
	
	return;
}

void testF(){

	return;
}
