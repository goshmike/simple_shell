#include "main.h"

/**
* stringLength - Returns the length of a string.
* @str: The string whose length is to be determined.
*
* Return: The integer length of the string.
*/
int stringLength(char *str)
{
int length = 0;

if (!str)
{
return (0);
}

while (*str++)
{
length++;
}

return (length);
}

/**
* stringCompare - Performs lexicographic comparison of two strings.
* @str1: The first string.
* @str2: The second string.
*
* Return: Negative if str1 < str2, positive if str1 > str2, zero if str1 == str2.
*/
int stringCompare(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
{
return (*str1 - *str2);
}

str1++;
str2++;
}

if (*str1 == *str2)
{
return (0);
}
else
{
return (*str1 < *str2 ? -1 : 1);
}
}

/**
* startsWith - Checks if a string starts with a specified substring.
* @str: The string to search.
* @prefix: The substring to find at the beginning of the string.
*
* Return: Address of the next character after the prefix in str, or NULL if not found.
*/
char *startsWith(const char *str, const char *prefix)
{
while (*prefix)
{
if (*prefix++ != *str++)
{
return (NULL);
}
}

return ((char *)str);
}

/**
* stringConcatenate - Concatenates two strings.
* @destination: The destination buffer.
* @source: The source buffer.
*
* Return: Pointer to the destination buffer.
*/
char *stringConcatenate(char *destination, char *source)
{
char *result = destination;

while (*destination)
{
destination++;
}

while (*source)
{
*destination++ = *source++;
}

*destination = *source;
return (result);
}

