#include "main.h"

/**
* bufferInput - Reads and buffers chained commands.
* @info: Parameter structure.
* @buffer: Address of buffer.
* @length: Address of length variable.
*
* Return: Bytes read.
*/
ssize_t bufferInput(info_t *info, char **buffer, size_t *length)
{
ssize_t bytesRead = 0;
size_t bufferLength = 0;

if (!*length) /* If the buffer is empty, fill it */
{
free(*buffer);
*buffer = NULL;
signal(SIGINT, handleSigint);
#if USE_GETLINE
bytesRead = getline(buffer, &bufferLength, stdin);
#else
bytesRead = customGetline(info, buffer, &bufferLength);
#endif
if (bytesRead > 0)
{
if ((*buffer)[bytesRead - 1] == '\n')
{
(*buffer)[bytesRead - 1] = '\0'; /* Remove trailing newline */
bytesRead--;
}
info->lineCountFlag = 1;
removeComments(*buffer);
addToHistory(info, *buffer, info->histCount++);
/* Check if it's a command chain */
{
*length = bytesRead;
info->cmdBuffer = buffer;
}
}
}
return (bytesRead);
}

/**
* getInput - Gets a line without the newline character.
* @info: Parameter structure.
*
* Return: Bytes read.
*/
ssize_t getInput(info_t *info)
{
static char *cmdBuffer; /* Buffer for command chain with ';' */
static size_t i, j, length;
ssize_t bytesRead = 0;
char **commandBufferPointer = &(info->arguments), *p;

_putchar(BUFFER_FLUSH);
bytesRead = bufferInput(info, &cmdBuffer, &length);
if (bytesRead == -1) /* EOF */
return (-1);
if (length) /* Commands left in the chain buffer */
{
j = i; /* Initialize a new iterator to the current buffer position */
p = cmdBuffer + i; /* Get a pointer for return */

checkCommandChain(info, cmdBuffer, &j, i, length);
while (j < length) /* Iterate to semicolon or end */
{
if (isCommandChain(info, cmdBuffer, &j))
break;
j++;
}

i = j + 1; /* Increment past nullified ';' */
if (i >= length) /* Reached the end of the buffer? */
{
i = length = 0; /* Reset position and length */
info->cmdBufferType = CMD_NORMAL;
}

*commandBufferPointer = p; /* Pass back the pointer to the current command position */
return (_strlen(p)); /* Return the length of the current command */
}

*commandBufferPointer = cmdBuffer; /* Not a chain, pass back the buffer from customGetline() */
return (bytesRead); /* Return the length of the buffer from customGetline() */
}

/**
* readBuffer - Reads a buffer.
* @info: Parameter structure.
* @buffer: Buffer.
* @index: Size.
*
* Return: Bytes read.
*/
ssize_t readBuffer(info_t *info, char *buffer, size_t *index)
{
ssize_t bytesRead = 0;

if (*index)
return (0);
bytesRead = read(info->readfd, buffer, READ_BUFFER_SIZE);
if (bytesRead >= 0)
*index = bytesRead;
return (bytesRead);
}

/**
* customGetline - Gets the next line of input from STDIN.
* @info: Parameter structure.
* @ptr: Address of pointer to buffer, preallocated or NULL.
* @length: Size of preallocated ptr buffer if not NULL.
*
* Return: Size.
*/
int customGetline(info_t *info, char **ptr, size_t *length)
{
static char buffer[READ_BUFFER_SIZE];
static size_t currentIndex, bufferLength;
size_t k;
ssize_t bytesRead = 0, size = 0;
char *p = NULL, *newP = NULL, *c;

p = *ptr;
if (p && length)
size = *length;
if (currentIndex == bufferLength)
currentIndex = bufferLength = 0;

bytesRead = readBuffer(info, buffer, &bufferLength);
if (bytesRead == -1 || (bytesRead == 0 && bufferLength == 0))
return (-1);

c = _strchr(buffer + currentIndex, '\n');
k = c ? 1 + (unsigned int)(c - buffer) : bufferLength;
newP = _realloc(p, size, size ? size + k : k + 1);
if (!newP) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);

if (size)
_strncat(newP, buffer + currentIndex, k - currentIndex);
else
_strncpy(newP, buffer + currentIndex, k - currentIndex + 1);

size += k - currentIndex;
currentIndex = k;
p = newP;

if (length)
*length = size;
*ptr = p;
return (size);
}

/**
* handleSigint - Blocks Ctrl-C.
* @signalNum: The signal number.
*
* Return: Void.
*/
void handleSigint(__attribute__((unused))int signalNum)
{
_puts("\n");
_puts("$ ");
_putchar(BUFFER_FLUSH);
}

