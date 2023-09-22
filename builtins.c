#include "main.h"

/**
* myHistory - Displays the history list, one command per line, preceded
*              by line numbers, starting at 0.
* @info: Pointer to the structure containing potential arguments.
*
* Return: Always 0.
*/
int myHistory(info_t *info)
{
printList(info->history);
return (0);
}

/**
* unsetAlias - Unsets an alias by removing it from the alias list.
* @info: Pointer to the parameter struct.
* @str: The alias string to unset.
*
* Return: 0 on success, 1 on error.
*/
int unsetAlias(info_t *info, char *str)
{
char *equalsPos, originalChar;
int ret;

equalsPos = _strchr(str, '=');
if (!equalsPos)
return (1);

originalChar = *equalsPos;
*equalsPos = '\0';

ret = deleteNodeAtIndex(&(info->alias), getNodeIndex(info->alias, nodeStartsWith(info->alias, str, -1)));

*equalsPos = originalChar;
return (ret);
}

/**
* setAlias - Sets an alias to a string.
* @info: Pointer to the parameter struct.
* @str: The string containing the alias.
*
* Return: 0 on success, 1 on error.
*/
int setAlias(info_t *info, char *str)
{
char *equalsPos;

equalsPos = _strchr(str, '=');
if (!equalsPos)
return (1);

if (!*++equalsPos)
return (unsetAlias(info, str));

unsetAlias(info, str);
return (addNodeEnd(&(info->alias), str, 0) == NULL);
}

/**
* printAlias - Prints an alias string.
* @node: The alias node.
*
* Return: 0 on success, 1 on error.
*/
int printAlias(list_t *node)
{
char *equalsPos = NULL, *aliasName = NULL;

if (node)
{
equalsPos = _strchr(node->str, '=');
for (aliasName = node->str; aliasName <= equalsPos; aliasName++)
_putchar(*aliasName);

_putchar('\'');
_puts(equalsPos + 1);
_puts("'\n");
return (0);
}

return (1);
}

/**
* myAlias - Mimics the alias builtin (man alias).
* @info: Pointer to the parameter struct.
*
* Return: 0.
*/
int myAlias(info_t *info)
{
int i = 0;
char *equalsPos = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
printAlias(node);
node = node->next;
}
return (0);
}

for (i = 1; info->argv[i]; i++)
{
equalsPos = _strchr(info->argv[i], '=');
if (equalsPos)
setAlias(info, info->argv[i]);
else
printAlias(nodeStartsWith(info->alias, info->argv[i], '='));
}

return (0);
}

