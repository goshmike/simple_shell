#include "main.h"

/**
* splitString - Splits a string into words using a specified delimiter.
* @str: The input string to be split.
* @delimiter: The delimiter used for splitting.
*
* Return: A pointer to an array of strings, or NULL on failure.
*/
char **splitString(char *str, char *delimiter)
{
int i, j, k, m, numWords = 0;
char **wordsArray;

if (str == NULL || str[0] == 0)
return (NULL);
if (!delimiter)
delimiter = " ";
for (i = 0; str[i] != '\0'; i++)
if (!isDelimiter(str[i], delimiter) &&
(isDelimiter(str[i + 1], delimiter) || !str[i + 1]))
numWords++;

if (numWords == 0)
return (NULL);
wordsArray = malloc((1 + numWords) *sizeof(char *));
if (!wordsArray)
return (NULL);
for (i = 0, j = 0; j < numWords; j++)
{
while (isDelimiter(str[i], delimiter))
i++;
k = 0;
while (!isDelimiter(str[i + k], delimiter) && str[i + k])
k++;
wordsArray[j] = malloc((k + 1) * sizeof(char));
if (!wordsArray[j])
{
for (k = 0; k < j; k++)
free(wordsArray[k]);
free(wordsArray);
return (NULL);
}
for (m = 0; m < k; m++)
wordsArray[j][m] = str[i++];
wordsArray[j][m] = 0;
}
wordsArray[j] = NULL;
return (wordsArray);
}

/**
* splitStringWithDelimiter - Splits a string into words using a spec char delimiter.
* @str: The input string to be split.
* @delimiter: The character delimiter used for splitting.
*
* Return: A pointer to an array of strings, or NULL on failure.
*/
char **splitStringWithDelimiter(char *str, char delimiter)
{
int i, j, k, m, numWords = 0;
char **wordsArray;

if (str == NULL || str[0] == 0)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != delimiter && str[i + 1] == delimiter) ||
(str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
numWords++;
if (numWords == 0)
return (NULL);
wordsArray = malloc((1 + numWords) *sizeof(char *));
if (!wordsArray)
return (NULL);
for (i = 0, j = 0; j < numWords; j++)
{
while (str[i] == delimiter && str[i] != delimiter)
i++;
k = 0;
while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
k++;
wordsArray[j] = malloc((k + 1) * sizeof(char));
if (!wordsArray[j])
{
for (k = 0; k < j; k++)
free(wordsArray[k]);
free(wordsArray);
return (NULL);
}
for (m = 0; m < k; m++)
wordsArray[j][m] = str[i++];
wordsArray[j][m] = 0;
}
wordsArray[j] = NULL;
return (wordsArray);
}

