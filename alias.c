#include "main.h"

/**
* input_buf - Function to buffer chained commands.
* @info: Pointer to the parameter struct.
* @buf: Pointer to the address of the buffer.
* @len: Pointer to the address of the length variable.
*
* Return: The number of bytes read.
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;

if (!*len) /* If there is nothing left in the buffer, fill it. */
{
/*bfree((void **)info->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
r = getline(buf, &len_p, stdin);
#else
r = _getline(info, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /* Remove trailing newline. */
r--;
}
info->linecount_flag = 1;
remove_comments(*buf);
build_history_list(info, *buf, info->histcount++);
/* Check if (_strchr(*buf, ';')) - Is this a command chain? */
{
*len = r;
info->cmd_buf = buf;
}
}
}
return (r);
}

/**
* get_input - Function to get a line minus the newline.
* @info: Pointer to the parameter struct.
*
* Return: The number of bytes read.
*/
ssize_t get_input(info_t *info)
{
static char *buf; /* The ';' command chain buffer. */
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(info->arg), *p;

_putchar(BUF_FLUSH);
r = input_buf(info, &buf, &len);
if (r == -1) /* If EOF is reached. */
return (-1);
if (len) /* If we have commands left in the chain buffer. */
{
j = i; /* Initialize a new iterator to the current buf position. */
p = buf + i; /* Get a pointer for return. */

check_chain(info, buf, &j, i, len);
while (j < len) /* Iterate to semicolon or end. */
{
if (is_chain(info, buf, &j))
break;
j++;
}

i = j + 1; /* Increment past nulled ';'' */
if (i >= len) /* Reached the end of the buffer? */
{
i = len = 0; /* Reset position and length. */
info->cmd_buf_type = CMD_NORM;
}

*buf_p = p; /* Pass back a pointer to the current command position. */
return (_strlen(p)); /* Return the length of the current command. */
}

*buf_p = buf; /* Else not a chain, pass back the buffer from _getline() */
return (r); /* Return the length of the buffer from _getline() */
}

/**
* read_buf - Function to read a buffer.
* @info: Pointer to the parameter struct.
* @buf: The buffer.
* @i: The size.
*
* Return: r
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
ssize_t r = 0;

if (*i)
return (0);
r = read(info->readfd, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}

/**
* _getline - Function to get the next line of input from STDIN.
* @info: Pointer to the parameter struct.
* @ptr: Pointer to the address of the pointer to the buffer, or NULL.
* @length: The size of the preallocated ptr buffer if not NULL.
*
* Return: s
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;

r = read_buf(info, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);

c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);

if (s)
_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
* sigintHandler - Function to block ctrl-C.
* @sig_num: The signal number.
*
* Return: void
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}

