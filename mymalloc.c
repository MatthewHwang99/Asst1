#include "mymalloc.h"

int getNextAddr(struct metadata* currNode){
	return currNode->size+sizeof(struct metadata);
}

void* mymalloc(int size, char* fileName, int lineNum){
  //check to see if the size is valid
  if(size < 0 || size > (4096 - sizeof(struct metadata))){
    printf("Error at line %d in file %s: Invalid size.\n", lineNum, fileName);
  }
  
  struct metadata* ptr = (struct metadata*)myblock;
  if(ptr->isFree != 'y' || ptr->isFree != 'n'){
    //First time mymalloc is run
    struct metadata first = {'y', (4096-sizeof(struct metadata))};
    *ptr = first;
    ptr = &(ptr+sizeof(struct metadata));
    //double check to make sure this is the correct output; should be a pointer to the new data block
    return (void*)ptr;
  }

  //Iterate through entire array until a free metadata is found with enough size
  while((char*)ptr <= &myblock[4095]){
    if(ptr->isFree == 'y'){
      if(ptr->size >= size){
		//block of mem. is free and is big enough
		if((ptr->size - size) > sizeof(struct metadata)){
		  //there is enough room for another block of memory
		  struct metadata new = {'y', (ptr->size - size - sizeof(struct metadata))};
		  *(ptr + size) = new;
		  ptr->size = size;
		  ptr->isFree = 'n';
		  ptr += sizeof(struct metadata);
		  //ptr = &myblock[ptr+sizeof(struct metadata)];
		}else{
		  //isn't enough space for another metadata struct and more memory so just return the whole block of memory
		  ptr->isFree = 'n';
		  ptr += sizeof(struct metadata);
		  //ptr = &myblock[ptr+sizeof(struct metadata)];
		}
		return (void*)ptr;
      }
    }
    //Seg fault???
    //or
    //ptr = &(ptr+sizeof(struct metadata));
    //this or ptr = (struct metadata*)&myblock[getNextAddr(ptr)];
    /*this*/ ptr += sizeof(struct metadata);
  }
  //if you get here we could not process the request  
  return NULL;
}


void myfree(void* pointer, char* filename, int lineNum){
	if(pointer == NULL){ //no operation is performed is ptr is NULL
		return; 
	}
	
	struct metadata* ptr = pointer - sizeof(struct metadata); //move ptr to the metadata of the data being free'd
	
	//A: Free()ing addresses that are not pointers:
	if( !((char*)ptr >= &myblock[0] && (char*)ptr <= &myblock[4095]) ){
		printf("Error at line %d in file %s: Address is not a pointer.\n", lineNum, filename);
		return;
	}
	
	//B: Free()ing pointers that were not allocated by malloc():
	//Check each md block to see if ptr is one of the mem block's that were malloc'd
	struct metadata* temp = (struct metadata*)(myblock);
	int pos = 0;
	while(pos < 4096){
		if(temp != ptr){
			pos = getNextAddr(temp);
			temp = (struct metadata*)(myblock+pos);
		}else{
			break; //temp == ptr | ptr was allocated by mymalloc
		}
	}
	
	if(pos > 4096){
		printf("Error at line %d in file %s: Cannot free pointer-- was not allocated by malloc().\n", lineNum, filename);
		return;
	}
	
	//C: Redundant free()ing of the same pointer:
	struct metadata* mdPtr = (struct metadata*) ptr;
	if(mdPtr->isFree == 'y'){
		printf("Error at line %d in file %s: Pointer was already free'd.\n", lineNum, filename);
		return;
	}
	
	//Since none of the conditions were met above, we can safely free the pointer
	mdPtr->isFree = 'y';
	
	//Iterate through the metadatas and combined adjacent blocks of memory that are free
	temp = (struct metadata*)(myblock);
	struct metadata* prev = temp;
	pos = getNextAddr(temp);
	temp = (struct metadata*)(myblock+pos);
	
	while(pos < 4096){
		if(temp->isFree == 'y' && prev->isFree == 'y'){ //adj blocks are free, combine them
			prev->size += (temp->size+sizeof(struct metadata));
			pos = getNextAddr(temp);
			temp = (struct metadata*)(myblock+pos); //keep prev where it is in case the md after temp is also free
		}else{
			pos = getNextAddr(temp);
			prev = temp;
			temp = (struct metadata*)(myblock+pos);
		}
	}
	
	return;
}
