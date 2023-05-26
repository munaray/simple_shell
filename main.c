#include "shell.h"

/**
 * main - This is the main loop shell for the UNIX shell.
 * @argc: This stands for argument count.
 *@argv: This stands for argument vector.
 *Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *retLastExeCmd = &retn;
	char *prompt = "sam@munaray> ", *nl = "\n";

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
		write(STDOUT_FILENO, prompt, _strlen(prompt));
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
