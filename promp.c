#include "main.h"

/**
* is_executable - Determines if a file is an executable command.
* @info: Pointer to the info struct.
* @path: Path to the file.
*
* Return: 1 if the file is executable, 0 otherwise.
*/
int is_executable(info_t *info, char *path)
{
struct stat st;

(void)info;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
* copy_chars - Copies characters from a string to a new buffer.
* @pathstr: The PATH string.
* @start: Starting index.
* @stop: Stopping index.
*
* Return: Pointer to a new buffer containing the copied characters.
*/
char *copy_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}

/**
* find_command_in_path - Finds a command in the PATH string.
* @info: Pointer to the info struct.
* @pathstr: The PATH string.
* @cmd: The command to find.
*
* Return: The full path of the command if found, or NULL if not found.
*/
char *find_command_in_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((_string_length(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_executable(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = copy_chars(pathstr, curr_pos, i);
if (!*path)
_string_concat(path, cmd);
else
{
_string_concat(path, "/");
_string_concat(path, cmd);
}
if (is_executable(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}

