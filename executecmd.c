#include "shell.h"

/**
 * getPid - This gets the current process ID.
 * Return: current pid on success else NULL.
 */
char *getPid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * execute - This xecutes a cmd in a child process.
 * @args: An array of arguments.
 * @argStart: A double pointer to the beginning of args.
 *
 * Return: the exit value of the last executed cmd on success.
 */
int execute(char **args, char **argStart)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = handleCmdByPath(cmd);
	}

	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (createError(args, 126));
		else
			ret = (createError(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				ret = (createError(args, 126));
			freeEnv();
			freeArgs(args, argStart);
			freeAliasList(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (ret);
}

