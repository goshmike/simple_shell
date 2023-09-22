#include "main.h"

/**
* _string_copy - Copies a string.
* @dest: The destination.
* @src: The source.
*
* Return: Pointer to the destination.
*/
char *_string_copy(char *dest, char *src)
{
int i = 0;

if (dest == src || src == NULL)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = '\0';
return (dest);
}

/**
* _string_duplicate - Duplicates a string.
* @str: The string to duplicate.
*
* Return: Pointer to the duplicated string.
*/
char *_string_duplicate(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
* _put_string - Prints an input string.
* @str: The string to be printed.
*
* Return: Nothing.
*/
void _put_string(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_put_character(str[i]);
i++;
}
}

/**
* _put_character - Writes the character 'c' to stdout.
* @c: The character to print.
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _put_character(char c)
{
static int i;
static char buf[WRITE_BUFFER_SIZE];

if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUFFER_FLUSH)
buf[i++] = c;
return (1);
}
