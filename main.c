#include "main.h"

/**
* main - Entry point for the Simple Shell.
* @argc: Argument count.
* @argv: Argument vector.
*
* Return: 0 on success, 1 on error.
*/
int main(int argc, char **argv)
{
info_t shell_info[] = {INFO_INIT};
int file_descriptor = 2;

/* Redirect standard error (fd = 2) to the provided file descriptor */
asm("mov %1, %0\n\t"
"add $3, %0"
: "=r" (file_descriptor)
: "r" (file_descriptor));

if (argc == 2)
{
/* Try to open the specified file for reading */
file_descriptor = open(argv[1], O_RDONLY);
if (file_descriptor == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
_eputs(argv[0]);
_eputs(": 0: Can't open ");
_eputs(argv[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
shell_info->readfd = file_descriptor;
}

/* Populate the environment list */
populate_environment_list(shell_info);

/* Read command history from a file */
read_history_from_file(shell_info);

/* Start the Simple Shell */
simple_shell(shell_info, argv);

return (EXIT_SUCCESS);
}

