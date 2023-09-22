#include "main.h"

/**
* Function: get_environ
* ---------------------
* Retrieves a copy of the environment variable array.
*
* @info: Structure containing potential arguments. Used for consistency.
*
* Returns: A string array representing the environment variables.
*/
char **get_environ(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_strings(info->env);
info->env_changed = 0;
}

return (info->environ);
}

/**
* Function: _unsetenv
* -------------------
* Removes an environment variable.
*
* @info: Structure containing potential arguments. Used for consistency.
* @var: The name of the environment variable to remove.
*
* Returns: 1 on successful deletion, 0 otherwise.
*/
int _unsetenv(info_t *info, char *var)
{
list_t *node = info->env;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = startswith(node->str, var);
if (p && *p == '=')
{
info->env_changed = delete_node_at_index(&(info->env), i);
i = 0;
node = info->env;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}

/**
* Function: _setenv
* -----------------
* Initializes or modifies an environment variable.
*
* @info: Structure containing potential arguments. Used for consistency.
* @var: The name of the environment variable.
* @value: The value to set for the environment variable.
*
* Returns: Always 0.
*/
int _setenv(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
strcpy(buf, var);
strcat(buf, "=");
strcat(buf, value);
node = info->env;
while (node)
{
p = startswith(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}

