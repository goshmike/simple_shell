#include "main.h"

/**
* strToInteger - Converts a string to an integer.
* @s: The string to be converted.
*
* Return: The converted number if valid, or -1 on error.
*/
int strToInteger(char *s)
{
int i = 0;
unsigned long int result = 0;

if (*s == '+')
s++; /* Skip leading plus sign */

for (i = 0; s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1); /* Overflow */
}
else
return (-1); /* Invalid character */
}

return (result);
}

/**
* printError - Prints an error message.
* @info: Pointer to the parameter and return info structure.
* @errorString: String containing the specified error type.
*/
void printError(info_t *info, char *errorString)
{
_eputs(info->fname);
_eputs(": ");
printDecimal(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(errorString);
}

/**
* printDecimal - Prints a decimal (integer) number (base 10).
* @input: The integer to be printed.
* @fd: The file descriptor to write to.
*
* Return: The number of characters printed.
*/
int printDecimal(int input, int fd)
{
int (*printChar)(char) = _putchar;
int i, count = 0;
unsigned int absolute, current;

if (fd == STDERR_FILENO)
printChar = _eputchar;

if (input < 0)
{
absolute = -input;
printChar('-');
count++;
}
else
absolute = input;

current = absolute;

for (i = 1000000000; i > 1; i /= 10)
{
if (absolute / i)
{
printChar('0' + current / i);
count++;
}
current %= i;
}

printChar('0' + current);
count++;

return (count);
}

/**
* convertNumber - Converts a number to a string.
* @num: The number to convert.
* @base: The base for the conversion.
* @flags: Argument flags.
*
* Return: The resulting string.
*/
char *convertNumber(long int num, int base, int flags)
{
static char *digits;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}

digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do {
*--ptr = digits[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;

return (ptr);
}

/**
* removeComments - Replaces the first instance of '#' with '\0'.
* @buf: The address of the string to modify.
*/
void removeComments(char *buf)
{
int i;

for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}

