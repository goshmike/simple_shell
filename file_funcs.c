#include "main.h"

/**
* getHistoryFilePath - Generates the file path for storing command history.
* @info: Pointer to the parameter structure.
*
* Return: Allocated string containing the history file path.
*/

char *getHistoryFilePath(info_t *info)
{
char *historyPath, *userHomeDir;

userHomeDir = getUserHomeDirectory(info);
if (!userHomeDir)
return (NULL);

historyPath = malloc(sizeof(char) * (stringLength(userHomeDir) + stringLength(HISTORY_FILENAME) + 2));
if (!historyPath)
return (NULL);

historyPath[0] = 0;
stringCopy(historyPath, userHomeDir);
stringConcat(historyPath, "/");
stringConcat(historyPath, HISTORY_FILENAME);

return (historyPath);
}

/**
* saveHistory - Creates or appends to an existing file for storing history.
* @info: Pointer to the parameter structure.
*
* Return: 1 on success, -1 on failure.
*/
int saveHistory(info_t *info)
{
ssize_t fileDescriptor;
char *filename = getHistoryFilePath(info);
list_t *node = NULL;

if (!filename)
return (-1);

fileDescriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);

if (fileDescriptor == -1)
return (-1);

for (node = info->commandHistory; node; node = node->next)
{
writeToFile(fileDescriptor, node->str);
writeToFile(fileDescriptor, '\n');
}
writeToFile(fileDescriptor, BUFFER_FLUSH);
close(fileDescriptor);

return (1);
}

/**
* loadHistory - Reads command history from a file.
* @info: Pointer to the parameter structure.
*
* Return: Number of history entries on success, 0 on failure.
*/
int loadHistory(info_t *info)
{
int i, last = 0, entryCount = 0;
ssize_t fileDescriptor, bytesRead, fileSize = 0;
struct stat fileStat;
char *buffer = NULL, *filename = getHistoryFilePath(info);

if (!filename)
return (0);

fileDescriptor = open(filename, O_RDONLY);
free(filename);

if (fileDescriptor == -1)
return (0);

if (!fileStatInfo(fileDescriptor, &fileStat))
fileSize = fileStat.st_size;

if (fileSize < 2)
return (0);

buffer = malloc(sizeof(char) * (fileSize + 1));
if (!buffer)
return (0);

bytesRead = read(fileDescriptor, buffer, fileSize);
buffer[fileSize] = 0;

if (bytesRead <= 0)
return (free(buffer), 0);

close(fileDescriptor);

for (i = 0; i < fileSize; i++)
{
if (buffer[i] == '\n')
{
buffer[i] = 0;
addToCommandHistory(info, buffer + last, entryCount++);
last = i + 1;
}
}

if (last != i)
addToCommandHistory(info, buffer + last, entryCount++);

free(buffer);
info->historyEntryCount = entryCount;

while (info->historyEntryCount-- >= HISTORY_MAX)
removeNodeAtIndex(&(info->commandHistory), 0);

updateHistoryEntryNumbers(info);

return (info->historyEntryCount);
}

/**
* addToCommandHistory - Adds a command entry to the history linked list.
* @info: Pointer to the parameter structure.
* @buffer: The command buffer to add.
* @entryCount: The history entry count.
*
* Return: Always 0.
*/
int addToCommandHistory(info_t *info, char *buffer, int entryCount)
{
list_t *node = NULL;

if (info->commandHistory)
node = info->commandHistory;

appendNode(&node, buffer, entryCount);

if (!info->commandHistory)
info->commandHistory = node;

return (0);
}

/**
* updateHistoryEntryNumbers - Updates history entry numbers after changes.
* @info: Pointer to the parameter structure.
*
* Return: The new history entry count.
*/
int updateHistoryEntryNumbers(info_t *info)
{
list_t *node = info->commandHistory;
int i = 0;

while (node)
{
node->number = i++;
node = node->next;
}

return (info->historyEntryCount = i);
}

