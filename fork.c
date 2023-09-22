#include "main.h"

/**
* clearInfo - Initialize fields of the info_t struct.
* @info: Pointer to the info_t struct to be cleared.
*/
void clearInfo(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
* setInfo - Initialize fields of the info_t struct based on command-line arguments.
* @info: Pointer to the info_t struct to be initialized.
* @av: Argument vector (command-line arguments).
*/
void setInfo(info_t *info, char **av)
{
int i = 0;

info->fname = av[0];

if (info->arg)
{
info->argv = splitString(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = duplicateString(info->arg);
info->argv[1] = NULL;
}
}

for (i = 0; info->argv && info->argv[i]; i++)
;
info->argc = i;

replaceAliases(info);
replaceVariables(info);
}
}

/**
* freeInfo - Free memory allocated for fields of the info_t struct.
* @info: Pointer to the info_t struct.
* @all: True if freeing all fields.
*/
void freeInfo(info_t *info, int all)
{
freeStringArray(info->argv);
info->argv = NULL;
info->path = NULL;

if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
freeList(&(info->env));
if (info->history)
freeList(&(info->history));
if (info->alias)
freeList(&(info->alias));
freeStringArray(info->environ);
info->environ = NULL;
freeBufferedCommands((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
writeCharToStdout(BUFFER_FLUSH);
}
}

