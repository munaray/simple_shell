#include "shell.h"

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *retLastExeCmd = &retn;
	char *prompt = "$ ", *nl = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, handleSignal);

	*retLastExeCmd = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = processCmdFromFile(argv[1], retLastExeCmd);
		freeEnv();
		freeAliasList(aliases);
		return (*retLastExeCmd);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = argsHandler(retLastExeCmd);
		freeEnv();
		freeAliasList(aliases);
		return (*retLastExeCmd);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = argsHandler(retLastExeCmd);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, nl, 1);
			freeEnv();
			freeAliasList(aliases);
			exit(*retLastExeCmd);
		}
	}

	freeEnv();
	freeAliasList(aliases);
	return (*retLastExeCmd);
}
