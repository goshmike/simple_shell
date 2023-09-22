#include "main.h"

/**
* shell_loop - Main shell loop.
* @info: The parameter & return info struct.
* @av: The argument vector from main().
*
* Return: 0 on success, 1 on error, or error code.
*/
int shell_loop(info_t *info, char **av)
{
ssize_t read_result = 0;
int builtin_ret = 0;

while (read_result != -1 && builtin_ret != -2)
{
clear_info(info);

if (is_interactive(info))
_puts("$ ");

_eputchar(BUF_FLUSH);

read_result = get_input(info);

if (read_result != -1)
{
set_info(info, av);
builtin_ret = find_builtin_command(info);

if (builtin_ret == -1)
find_external_command(info);
}
else if (is_interactive(info))
_putchar('\n');

free_info(info, 0);
}

write_history(info);
free_info(info, 1);

if (!is_interactive(info) && info->status)
exit(info->status);

if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}

return (builtin_ret);
}

/**
* find_builtin_command - Finds a built-in command.
* @info: The parameter & return info struct.
*
* Return: -1 if built-in not found,
*         0 if built-in executed successfully,
*         1 if built-in found but not successful,
*         -2 if built-in signals exit().
*/
int find_builtin_command(info_t *info)
{
int i;
int builtin_result = -1;

builtin_table builtins[] = {
{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}
};

for (i = 0; builtins[i].command; i++)
{
if (_strcmp(info->argv[0], builtins[i].command) == 0)
{
info->line_count++;
builtin_result = builtins[i].function(info);
break;
}
}

return (builtin_result);
}

/**
* find_external_command - Finds an external command in PATH.
* @info: The parameter & return info struct.
*
* Return: void.
*/
void find_external_command(info_t *info)
{
char *path = NULL;

info->path = info->argv[0];

if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}

int arg_count = count_non_empty_args(info->arg);

if (!arg_count)
return;

path = find_command_in_path(info, _getenv(info, "PATH="), info->argv[0]);

if (path)
{
info->path = path;
execute_external_command(info);
}
else
{
if ((is_interactive(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && is_command_executable(info, info->argv[0]))
{
execute_external_command(info);
}
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}

/**
* execute_external_command - Forks and executes an external command.
* @info: The parameter & return info struct.
*
* Return: void.
*/
void execute_external_command(info_t *info)
{
pid_t child_pid = fork();

if (child_pid == -1)
{
perror("Error:");
return;
}

if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environment(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));

if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}

