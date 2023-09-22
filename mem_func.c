#include "main.h"

/**
* freeAndNull - Frees a pointer and sets it to NULL.
* @ptr: Address of the pointer to free
*
* Returns 1 if freed, otherwise 0.
*/
int freeAndNull(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}

/**
* fillMemory - Fills a memory block with a constant byte.
* @memBlock: The pointer to the memory block.
* @byteValue: The byte value to fill the memory with.
* @size: The size (in bytes) of the memory block.
*
* Returns a pointer to the filled memory block.
*/
char *fillMemory(char *memBlock, char byteValue, unsigned int size)
{
unsigned int i;

for (i = 0; i < size; i++)
{
memBlock[i] = byteValue;
}
return (memBlock);
}

/**
* freeArrayOfStrings - Frees an array of strings and its elements.
* @stringArray: The array of strings to free.
*/
void freeArrayOfStrings(char **stringArray)
{
char **currentPtr = stringArray;

if (!stringArray)
{
return;
}

while (*currentPtr)
{
free(*currentPtr++);
}

free(stringArray);
}

/**
* resizeMemoryBlock - Resizes a memory block.
* @blockPtr: Pointer to the previous memory block.
* @oldSize: Byte size of the previous memory block.
* @newSize: Byte size of the new memory block.
*
* Returns a pointer to the resized memory block.
*/
void *resizeMemoryBlock(
    void *blockPtr, unsigned int oldSize, unsigned int newSize
);
{
char *newBlock;
