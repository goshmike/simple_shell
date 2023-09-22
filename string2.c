#include "main.h"

/**
* stringCopy - Copies a string from source to destination.
* @destination: The destination string.
* @source: The source string.
*
* Return: Pointer to the destination string.
*/
char *stringCopy(char *destination, char *source)
{
int i = 0;

if (destination == source || source == NULL)
{
return (destination);
}

while (source[i])
{
destination[i] = source[i];
i++;
}

destination[i] = '\0';
return (destination);
}

/**
* stringDuplicate - Duplicates a string.
* @str: The string to duplicate.
*
* Return: Pointer to the duplicated string or NULL on failure.
*/
char *stringDuplicate(const char *str)
{
int length = 0;
char *duplicate;

if (str == NULL)
{
return (NULL);
}

while (*str++)
{
length++;
}

duplicate = malloc(sizeof(char) * (length + 1));

if (!duplicate)
{
return (NULL);
}

for (length++; length--;)
{
duplicate[length] = *--str;
}

return (duplicate);
}

/**
* printString - Prints a string to stdout.
* @str: The string to be printed.
*
* Return: Nothing.
*/
void printString(char *str)
{
int i = 0;

if (!str)
{
return;
}

while (str[i] != '\0')
{
printCharacter(str[i]);
i++;
}
}

/**
* printCharacter - Writes a character to stdout.
* @c: The character to print.
*
* Return: On success, 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int printCharacter(char c)
{
static int bufferIndex;
static char buffer[WRITE_BUFFER_SIZE];

if (c == FLUSH_BUFFER || bufferIndex >= WRITE_BUFFER_SIZE)
{
write(STDOUT_FILENO, buffer, bufferIndex);
bufferIndex = 0;
}

if (c != FLUSH_BUFFER)
{
buffer[bufferIndex++] = c;
}

return (1);
}

