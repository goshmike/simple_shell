#include "main.h"

/**
* list_length - Determines the length of a linked list.
* @head: Pointer to the first node.
*
* Return: The size of the list.
*/
size_t list_length(const list_t *head)
{
size_t count = 0;

while (head)
{
head = head->next;
count++;
}

return (count);
}

/**
* list_to_array - Converts a linked list to an array of strings.
* @head: Pointer to the first node.
*
* Return: An array of strings.
*/
char **list_to_array(list_t *head)
{
list_t *node = head;
size_t length = list_length(head);
char **strings;
char *str;

if (!head || !length)
return (NULL);

strings = malloc(sizeof(char *) * (length + 1));

if (!strings)
return (NULL);

for (size_t i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);

if (!str)
{
for (size_t j = 0; j < i; j++)
free(strings[j]);

free(strings);
return (NULL);
}

str = _strcpy(str, node->str);
strings[i] = str;
}

strings[length] = NULL;
return (strings);
}

/**
* print_list_elements - Prints all elements of a list_t linked list.
* @head: Pointer to the first node.
*
* Return: The size of the list.
*/
size_t print_list_elements(const list_t *head)
{
size_t count = 0;

while (head)
{
_puts(convert_number(head->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
count++;
}

return (count);
}

/**
* find_node_starts_with - Finds a node whose string starts with a prefix.
* @head: Pointer to the list head.
* @prefix: String to match.
* @next_char: The next character after the prefix to match.
*
* Return: The matching node or NULL.
*/
list_t *find_node_starts_with(list_t *head, char *prefix, char next_char)
{
char *p = NULL;

while (head)
{
p = starts_with(head->str, prefix);

if (p && ((next_char == -1) || (*p == next_char)))
return (head);

head = head->next;
}

return (NULL);
}

/**
* get_node_index - Gets the index of a node in a linked list.
* @head: Pointer to the list head.
* @node: Pointer to the node.
*
* Return: The index of the node or -1 if not found.
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
size_t index = 0;

while (head)
{
if (head == node)
return (index);

head = head->next;
index++;
}

return (-1);
}

