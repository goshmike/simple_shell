#include "main.h"

/**
* list_length - Determines the length of a linked list.
* @h: Pointer to the first node.
*
* Return: Size of the list.
*/
size_t list_length(const list_t *h)
{
size_t i = 0;

while (h)
{
h = h->next;
i++;
}
return (i);
}

/**
* list_to_string_array - Returns an array of strings from the list of node->str.
* @head: Pointer to the first node.
*
* Return: Array of strings.
*/
char **list_to_string_array(list_t *head)
{
list_t *node = head;
size_t i = list_length(head), j;
char **strs;
char *str;

if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_string_length(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}

str = _string_copy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}

/**
* print_linked_list - Prints all elements of a list_t linked list.
* @h: Pointer to the first node.
*
* Return: Size of the list.
*/
size_t print_linked_list(const list_t *h)
{
size_t i = 0;

while (h)
{
_put_string(convert_number(h->num, 10, 0));
_put_character(':');
_put_character(' ');
_put_string(h->str ? h->str : "(nil)");
_put_string("\n");
h = h->next;
i++;
}
return (i);
}

/**
* find_node_with_prefix - Returns the node whose string starts with the specified prefix.
* @node: Pointer to the list head.
* @prefix: String to match.
* @c: The next character after the prefix to match (-1 to ignore).
*
* Return: Matching node or NULL.
*/
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
char *p = NULL;

while (node)
{
p = starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
* get_node_index - Gets the index of a specific node in the linked list.
* @head: Pointer to the list head.
* @node: Pointer to the node.
*
* Return: Index of the node or -1 if not found.
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
size_t i = 0;

while (head)
{
if (head == node)
return (i);
head = head->next;
i++;
}
return (-1);
}

