#include "main.h"

/**
* retrieve_environment - Returns a copy of the environment variables as an array of strings.
* @info: Structure containing potential arguments.
*
* Return: A copy of the environment variables.
*/
char **retrieve_environment(info_t *info)
{
if (!info->environ || info->environment_changed)
{
info->environ = list_to_string_array(info->env);
info->environment_changed = 0;
}

return (info->environ);
}

/**
* remove_environment_variable - Removes an environment variable.
* @info: Structure containing potential arguments.
* @variable: The environment variable to remove.
*
* Return: 1 on success, 0 otherwise.
*/
int remove_environment_variable(info_t *info, char *variable)
{
list_t *node = info->env;
size_t index = 0;
char *p;

if (!node || !variable)
return 0;

while (node)
{
p = starts_with(node->str, variable);

if (p && *p == '=')
{
info->environment_changed = delete_node_at_index(&(info->env), index);
index = 0;
node = info->env;
continue;
}

node = node->next;
index++;
}

return (info->environment_changed);
}

/**
* set_environment_variable - Initializes a new environment variable or modifies an existing one.
* @info: Structure containing potential arguments.
* @variable: The environment variable name.
* @value: The environment variable value.
*
* Return: 0 on success, 1 on failure.
*/
int set_environment_variable(info_t *info, char *variable, char *value)
{
char *buffer = NULL;
list_t *node;
char *p;

if (!variable || !value)
return (1);

buffer = malloc(_strlen(variable) + _strlen(value) + 2);

if (!buffer)
return (1);

_strcpy(buffer, variable);
_strcat(buffer, "=");
_strcat(buffer, value);

node = info->env;

while (node)
{
p = starts_with(node->str, variable);

if (p && *p == '=')
{
free(node->str);
node->str = buffer;
info->environment_changed = 1;
return (0);
}

node = node->next;
}

add_node_end(&(info->env), buffer, 0);
free(buffer);
info->environment_changed = 1;
return (0);
}
