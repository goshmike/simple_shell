#include "main.h"

/**
* print_to_stderr - Prints a string to the standard error (stderr) stream.
* @str: The string to be printed to stderr.
*
* Return: Nothing.
*/
void print_to_stderr(char *str)
{
int i = 0;

if (!str)
return;

while (str[i] != '\0')
{
write_char_to_stderr(str[i]);
i++;
}
}

/**
* write_char_to_stderr - Writes a character to the standard error (stderr) stream.
* @c: The character to be written to stderr.
*
* Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
*/
int write_char_to_stderr(char c)
{
static int i;
static char buffer[WRITE_BUFFER_SIZE];

if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
{
write(2, buffer, i);
i = 0;
}

if (c != FLUSH_BUFFER)
buffer[i++] = c;

return (1);
}

/**
* write_char_to_fd - Writes a character to the specified file descriptor.
* @c: The character to be written.
* @fd: The file descriptor to write to.
*
* Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
*/
int write_char_to_fd(char c, int fd)
{
static int i;
static char buffer[WRITE_BUFFER_SIZE];

if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
{
write(fd, buffer, i);
i = 0;
}

if (c != FLUSH_BUFFER)
buffer[i++] = c;

return (1);
}

/**
* print_string_to_fd - Prints a string to the specified file descriptor.
* @str: The string to be printed.
* @fd: The file descriptor to write to.
*
* Return: The number of characters written.
*/
int print_string_to_fd(char *str, int fd)
{
int i = 0;

if (!str)
return (0);

while (*str)
{
i += write_char_to_fd(*str++, fd);
}

return (i);
}

