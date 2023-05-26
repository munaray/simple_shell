#include "shell.h"

/**
 * handleBuiltin - This join a cmd with its corresponding
 * builtin function.
 * @cmd: The cmd to match.
 * Return: A function pointer to the corresponding builtin.
 */
int (*handleBuiltin(char *cmd))(char **args, char **argStart)
{
	builtin_t funcs[] = {
		{ "exit", exitShell },
		{ "env", envShell },
		{ "setenv", setenvShell },
		{ "unsetenv", unsetenvShell },
		{ "cd", cdShell },
		{ "alias", handleAliasCmd },
		{ "help", helpShell },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, cmd) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * exitShell - A function that exit the shell when invoke.
 * @args: An array of arguments containing the exit value.
 * @argStart: A double pointer to the beginning of args.
 *
 * Return: if args is absent return -3.
 *         for invalid exit status return 2.
 *         else exits with the given status value.
 */
int exitShell(char **args, char **argStart)
{
	int i, numLen = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			numLen++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= numLen && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (createError(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (createError(--args, 2));
	args -= 1;
	freeArgs(args, argStart);
	freeEnv();
	freeAliasList(aliases);
	exit(num);
}

/**
 * cdShell - This changes the current directory of the shell.
 * @args: An array of arguments.
 * @argStart: A double pointer to the beginning of args.
 *
 * Return: on success return 0.
 */
int cdShell(char **args, char __attribute__((__unused__)) **argStart)
{
	char **dirInfo, *nl = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (createError(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (createError(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dirInfo = malloc(sizeof(char *) * 2);
	if (!dirInfo)
		return (-1);

	dirInfo[0] = "OLDPWD";
	dirInfo[1] = oldpwd;
	if (setenvShell(dirInfo, dirInfo) == -1)
		return (-1);

	dirInfo[0] = "PWD";
	dirInfo[1] = pwd;
	if (setenvShell(dirInfo, dirInfo) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, nl, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dirInfo);
	return (0);
}

/**
 * helpShell - This displays information about the builtin cmds.
 * @args: An array of arguments.
 * @argStart: A pointer to the beginning of args.
 *
 * Return: on success return 0.
 */
int helpShell(char **args, char __attribute__((__unused__)) **argStart)
{
	if (!args[0])
		displayAllHelp();
	else if (_strcmp(args[0], "alias") == 0)
		displayAliasHelp();
	else if (_strcmp(args[0], "cd") == 0)
		displayCdHelp();
	else if (_strcmp(args[0], "exit") == 0)
		displayExitHelp();
	else if (_strcmp(args[0], "env") == 0)
		displayEnvHelp();
	else if (_strcmp(args[0], "setenv") == 0)
		displaySetenvHelp();
	else if (_strcmp(args[0], "unsetenv") == 0)
		displayUnsetenvHelp();
	else if (_strcmp(args[0], "help") == 0)
		displayHelpMessage();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
