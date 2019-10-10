#include "mymalloc.h"

void* mymalloc(int size, char* filename, int lineNum){
	//check to see if the size is valid
	if(size < 0 || size > 4096){
		printf("Error at line %d in file %s:Invalid size.\n", lineNum, fileName);
	}

	char magic_num = 127; //used to check if mymalloc has been called yet...
	
	struct md* temp = (struct md*) myblock; 
	
	struct md* newMD;
	newMD.isFree = '0';
	newMD.size = size;
	newMD.next = NULL;
	
	if(myblock[0] != magic_num){ //check for mymalloc's first call
		myblock[0] = magic_num;
		temp = (char*)temp + 1;
		struct md* nextMD;
		nextMD.size = 4096 - (sizeof(struct md)*2 + size + 1); //size of the rest of myblock
		nextMD.isFree = 1; 
		nextMD.next = NULL;
		newMD.next = &nextMD;
		*temp = newMD;
		
		return (void*)( (char*)temp + sizeof(struct md)); //return location where the memory (not the MD) is pointing to
	}
	
	return;
}

void myfree(int size, char* filename, int lineNum){

	return;
}
