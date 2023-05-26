#include "shell.h"

/**
 * handleCmdByPath - Locates a cmd in the PATH.
 * @cmd: The cmd to locate.
 *
 * Return: If an error occurs or the cmd cannot be located - NULL.
 *         Otherwise - the full pathname of the cmd.
 */
char *handleCmdByPath(char *cmd)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = getDirByPath(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(cmd) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, cmd);

		if (stat(temp, &st) == 0)
		{
			freeList(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	freeList(head);

	return (NULL);
}

/**
 * fillDirByPath - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fillDirByPath(char *path)
{
	int i, length = 0;
	char *cp, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	cp = malloc(sizeof(char) * (length + 1));
	if (!cp)
		return (NULL);
	cp[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(cp, pwd);
				_strcat(cp, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(cp, ":");
				_strcat(cp, pwd);
			}
			else
				_strcat(cp, ":");
		}
		else
		{
			_strncat(cp, &path[i], 1);
		}
	}
	return (cp);
}

/**
 * getDirByPath - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *getDirByPath(char *path)
{
	int i;
	char **dirs, *cp;
	list_t *head = NULL;

	cp = fillDirByPath(path);
	if (!cp)
		return (NULL);
	dirs = _strtok(cp, ":");
	free(cp);
	if (!dirs)
		return (NULL);

	for (i = 0; dirs[i]; i++)
	{
		if (addNodeEnd(&head, dirs[i]) == NULL)
		{
			freeList(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
