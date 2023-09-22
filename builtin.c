#include "main.h"

/**
* exit_shell - Exit the shell
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*
* This function exits the shell with a given exit status.
* Returns:
* - 0 if info->arguments[0] is not equal to "exit".
* - Negative values to indicate exit status on success.
* - 1 in case of an illegal number error.
*/
int exit_shell(info_t *info)
{
int exit_status;

if (info->arguments[1]) 
{
exit_status = parse_exit_status(info->arguments[1]);
if (exit_status == -1) 
{
info->status = 2;
print_error(info, "Illegal number: ");
print_string(info->arguments[1]);
print_newline();
return (1);
}
info->err_num = exit_status;
return (-2);
}
info->err_num = -1;
return (-2);
}

/**
* change_directory - Change the current working directory of the process
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*
* This function changes the current working directory of the process.
* If no argument is provided, it defaults to the HOME directory.
* If the argument is "-", it switches to the previous directory.
* Returns: Always 0.
*/
int change_directory(info_t *info)
{
char *current_dir, *target_dir, buffer[1024];
int chdir_ret;

current_dir = get_current_directory(buffer, 1024);
if (!current_dir)
print_string("TODO: >>getcwd failure emsg here<<\n");
if (!info->arguments[1]) 
{
target_dir = get_environment_variable(info, "HOME=");
if (!target_dir)
chdir_ret = chdir((target_dir = get_environment_variable(info, "PWD=")) ? target_dir : "/");
else
chdir_ret = chdir(target_dir);
} else if (are_strings_equal(info->arguments[1], "-") == 0) {
if (!get_environment_variable(info, "OLDPWD=")) {
print_string(current_dir);
print_newline();
return 1;
}
print_string(get_environment_variable(info, "OLDPWD="));
print_newline();
chdir_ret = chdir((target_dir = get_environment_variable(info, "OLDPWD=")) ? target_dir : "/");
} else {
chdir_ret = chdir(info->arguments[1]);
}
if (chdir_ret == -1) {
print_error(info, "can't cd to ");
print_string(info->arguments[1]);
print_newline();
} else {
set_environment_variable(info, "OLDPWD", get_environment_variable(info, "PWD="));
set_environment_variable(info, "PWD", get_current_directory(buffer, 1024));
}
return (0);
}

/**
* help_shell - Display help information for the shell
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*
* This function displays help information for the shell commands.
* Returns: Always 0.
*/
int help_shell(info_t *info)
{
char **argument_array;

argument_array = info->arguments;
print_string("Help command is called. Functionality not implemented yet.\n");
if (0)
print_string(*argument_array); /* Temporary attribute unused workaround */
return (0);
}

