#include "mymalloc.h"

int main(int argc, char* argv){
  int i, j;
  char* p;
  //malloc() 1 byte and immediatly free it, 150 times
  for(i = 0; i < 150; i++){
    p = malloc(1);
    free(p);
  }
  //malloc() 1 byte, store the pointer in an array = do this 150 times
  //once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one
  char array[50];
  for(i = 0; i < 150; i++){
    if(i == 50){
      for(j = 0; j < i; j++){
	free(array[j]);
      }
    }

  }
}
