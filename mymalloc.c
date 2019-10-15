#include "mymalloc.h"

void* mymalloc(int size, char* filename, int lineNum){
  //check to see if the size is valid
  if(size < 0 || size > (4096 - sizeof(metadata))){
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
  while(ptr <= myblock[4095]){
    if(ptr->isFree == 'y'){
      if(ptr->size >= size){
	//block of mem. is free and is big enough
	if((ptr->size - size) > sizeof(struct metadata)){
	  //there is enough room for another block of memory
	  struct metadata new = {'y', (ptr->size - size - sizeof(metadata))};
	  *(ptr + size) = new;
	  ptr->size = size;
	  ptr->isFree = 'n';
	  ptr += sizeof(struct metadata);
	  //&myblock[ptr+sizeof(metadata)];
	}else{
	  //isn't enough space for another metadata struct and more memory so just return the whole block of memory
	  ptr->isFree = 'n';
	  ptr += sizeof(struct metadata);
	}
	return (void*)ptr;
      }
    }
    //Seg fault???
    //or
    //ptr = &(ptr+sizeof(struct metadata));
    ptr += sizeof(metadata);
    //&myblock[ptr+sizeof(struct metadata)];
  }
  //if you get here we could not process the request  
  return NULL;
}

void myfree(int size, char* filename, int lineNum){
  
  return;
}
