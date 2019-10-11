#include "mymalloc.h"

int getNextAddr(struct md currNode, int loc){
	return currNode.size+sizeof(struct md)+loc;
}

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

void myfree(void* ptr, char* filename, int lineNum){
	if(ptr == NULL){ //no operation is performed is ptr is NULL
		return; 
	}
	
	ptr = ptr - sizeof(struct md); //move ptr to the metadata of the data being free'd
	
	//A: Free()ing addresses that are not pointers:
	if( !(ptr > &myblock[0] && ptr <= &myblock[4095]) ){
		printf("Error at line %d in file %s: Address is not a pointer.\n", lineNum, filename);
		return;
	}
	
	//B: Free()ing pointers that were not allocated by malloc():
	//Check each md block to see if ptr is one of the mem block's that were malloc'd
	struct md* temp = (struct md*)(myblock+1);
	int pos = 1;
	while(pos < 4096){
		if(temp != ptr){
			pos = getNextAddr(temp, pos);
			temp = (struct md*)(myblock+pos);
		}else{
			break; //temp == ptr | ptr was allocated by mymalloc
		}
	}
	
	if(pos > 4096){
		printf("Error at line %d in file %s: Cannot free pointer-- was not allocated by malloc().\n", lineNum, filename);
		return;
	}
	
	//C: Redundant free()ing of the same pointer:
	struct md* mdPtr = (struct md*) ptr;
	if(mdPtr.isFree == '1'){
		printf("Error at line %d in file %s: Pointer was already free'd.\n", lineNum, filename);
		return;
	}
	
	//Since none of the conditions were met above, we can safely free the pointer
	mdPtr.isFree = '1';
	
	//Iterate through the metadatas and combined adjacent blocks of memory that are free
	struct md* temp = (struct md*)(myblock+1);
	struct md* prev = temp;
	pos = getNextAddr(temp, 1);
	temp = (struct md*)(myblock+pos);
	
	while(pos < 4096){
		if(temp.isFree == '1' && prev.isFree == '1'){ //adj blocks are free, combine them
			prev.size += (temp.size+sizeof(struct md));
			pos = getNextAddr(temp, pos);
			temp = (struct md*)(myblock+pos); //keep prev where it is in case the md after temp is also free
		}else{
			pos = getNextAddr(temp, pos);
			prev = temp;
			temp = (struct md*)(myblock+pos);
		}
	}
	
	return;
}
