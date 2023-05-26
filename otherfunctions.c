#include "shell.h"

/**
 * freeArgs - This frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @argStart: A double pointer to the beginning of args.
 */
void freeArgs(char **args, char **argStart)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(argStart);
}

/**
 * handleSignal - This prints a new prompt upon a signal.
 * @sig: The signal to be handled.
 */
void handleSignal(int sig)
{
	char *newPrompt = "\n$ ";

	(void)sig;
	signal(SIGINT, handleSignal);
	write(STDIN_FILENO, newPrompt, 3);
}
