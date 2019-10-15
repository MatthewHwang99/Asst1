In this assignment, we were required to create our own implementation of malloc() and free(). For our metadata struct, we wanted to be space efficient so we used a char (isFree) to store whether a block of memory is free (denoted with 'y') or not free ('n'), and a short (size) to store the amount of data being asked to be allocated. As a result, this gives us a metadata size of 3 bytes (due to padding, I think, sizeof(struct metadata) returns 4 bytes instead).
Mymalloc() design:

Myfree() design:
	For free(), we were required to implement a more "intelligent" version of it. First, we check if the pointer is not NULL (and return, otherwise). Then, we needed to move the pointer to point at the metadata instead of the block of memory. After that, we can check the three cases. (A) To check if the address is not a pointer, we check if the pointer is within the range of the our char array (myblock[0] <= pointer >= myblock[4095]). (B) Then, we make sure that the pointer was allocated by malloc() and not by the user by checking each metadata block in myblock and seeing if pointer is there. (C) Lastly, we make sure that the pointer has not been already free()'d. Once these cases are checked, we can free the metadata pointer.
	After all the above is completed, we iterate through myblock and check for adjacent blocks that are both free using two metadata pointers. If they are, the previous pointer will gain the size of the free block in front of it, and the size of the metadata.
	
Memgrind results:
