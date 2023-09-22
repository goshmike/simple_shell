#include "main.h"

/**
* isExecutable - It Determines if a file is an executable command.
* @info: The info struct.
* @path: Path to the file.
*
* Return: 1 if it's an executable, 0 otherwise.
*/
int isExecutable(info_t *info, char *path)
{
struct stat fileStat;

(void)info;

if (!path || stat(path, &fileStat) != 0)
{
return (0);
}

return (S_ISREG(fileStat.st_mode) ? 1 : 0);
}

/**
* copySubstring - Copies a substring of characters from pathstr.
* @pathstr: The PATH string.
* @start: Starting index.
* @stop: Stopping index.
*
* Return: Pointer to a new buffer containing the copied substring.
*/
char *copySubstring(char *pathstr, int start, int stop)
{
static char buffer[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
{
if (pathstr[i] != ':')
{
buffer[k++] = pathstr[i];
}
}

buffer[k] = '\0';
return (buffer);
}

/**
* findExecutablePath - Finds the full path of a command in the PATH string.
* @info: The info struct.
* @pathstr: The PATH string.
* @cmd: The command to find.
*
* Return: Full path of the command if found, or NULL if not found.
*/
char *findExecutablePath(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
{
return (NULL);
}

if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (isExecutable(info, cmd))
{
return (cmd);
}
}

while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = copySubstring(pathstr, curr_pos, i);

if (!*path)
{
_strcat(path, cmd);
}
else
{
_strcat(path, "/");
_strcat(path, cmd);
}

if (isExecutable(info, path))
{
return (path);
}

if (!pathstr[i])
{
break;
}

curr_pos = i;
}

i++;
}

return (NULL);
}

