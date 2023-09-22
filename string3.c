#include "main.h"

/**
* stringCopyN - Copies a string up to a specified length.
* @destination: The destination string.
* @source: The source string.
* @n: The maximum number of characters to copy.
*
* Return: Pointer to the destination string.
*/
char *stringCopyN(char *destination, char *source, int n)
{
int i, j;
char *result = destination;

i = 0;

while (source[i] != '\0' && i < n - 1)
{
destination[i] = source[i];
i++;
}

if (i < n)
{
j = i;

while (j < n)
{
destination[j] = '\0';
j++;
}
}

return (result);
}

/**
* stringConcatenateN - Concatenates two strings up to a specified length.
* @destination: The first string.
* @source: The second string.
* @n: The maximum number of bytes to concatenate.
*
* Return: Pointer to the concatenated string.
*/
char *stringConcatenateN(char *destination, char *source, int n)
{
int i, j;
char *result = destination;

i = 0;
j = 0;

while (destination[i] != '\0')
{
i++;
}

while (source[j] != '\0' && j < n)
{
destination[i] = source[j];
i++;
j++;
}

if (j < n)
{
destination[i] = '\0';
}

return (result);
}

/**
* stringFindCharacter - Locates a character in a string.
* @str: The string to be searched.
* @c: The character to look for.
*
* Return: Pointer to the first occurrence of the character in the string,
* or NULL if not found.
*/
char *stringFindCharacter(char *str, char c)
{
do {
if (*str == c)
{
return (str);
}
} while (*str++ != '\0');

return (NULL);
}
