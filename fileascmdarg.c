#include "shell.h"

/**
 * failToOpen - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @filePath: Path to the supposed file.
 *
 * Return: 127.
 */

int failToOpen(char *filePath)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(filePath) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, filePath);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * processCmdFromFile - Takes a file and attempts to run the commands stored
 * within.
 * @filePath: Path to the file.
 * @retLastExeCmd: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int processCmdFromFile(char *filePath, int *retLastExeCmd)
{
	ssize_t file, b_read, i;
	unsigned int lineSize = 0;
	unsigned int oldSize = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(filePath, O_RDONLY);
	if (file == -1)
	{
		*retLastExeCmd = failToOpen(filePath);
		return (*retLastExeCmd);
	}
	line = malloc(sizeof(char) * oldSize);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && lineSize == 0)
			return (*retLastExeCmd);
		buffer[b_read] = '\0';
		lineSize += b_read;
		line = _realloc(line, oldSize, lineSize);
		_strcat(line, buffer);
		oldSize = lineSize;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < lineSize; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < lineSize && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	replaceVariable(&line, retLastExeCmd);
	lineHandler(&line, lineSize);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (checkArgs(args) != 0)
	{
		*retLastExeCmd = 2;
		freeArgs(args, args);
		return (*retLastExeCmd);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = callArgs(args, front, retLastExeCmd);
			args = &args[++i];
			i = 0;
		}
	}

	ret = callArgs(args, front, retLastExeCmd);

	free(front);
	return (ret);
}
