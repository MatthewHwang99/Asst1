#include "mymalloc.h"

void* mymalloc(int size, char* filename, int lineNum){
  //check to see if the size is valid
  if(size < 0 || size > (4096 - sizeof(metadata))){
    printf("Error at line %d in file %s: Invalid size.\n", lineNum, fileName);
  }
  
  struct metadata* ptr = (struct metadata*)myblock;
  if(ptr->isFree != 'y' | ptr->isFree != 'n'){
    //First time mymalloc is run
    struct metadata first = {'y', (4096-sizeof(struct metadata))};
    *ptr = first;
    return ptr+sizeof(struct metadata);
  }
  //Iterate through entire array until a free metadata is found with enough size
  while(ptr <= myblock[4096]){
    if(ptr->isFree == 'y'){
      if(ptr->size >= size){
	//block of mem. is free and is big enough
      }
    }
    ptr = myblock[ptr+sizeof(struct metadata)];
  }
  
  
  return;
}

void myfree(int size, char* filename, int lineNum){
  
  return;
}
