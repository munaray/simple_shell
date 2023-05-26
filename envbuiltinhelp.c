#include "shell.h"

/**
 * displayEnvHelp - Displays information on the builtin command 'env'.
 */
void displayEnvHelp(void)
{
	char *output = "env: env\n\tDisplay the current environment variables.\n";

	write(STDOUT_FILENO, output, _strlen(output));
}

/**
 * displaySetenvHelp - Displays information on the builtin command 'setenv'.
 */
void displaySetenvHelp(void)
{
	char *output = "setenv: setenv [VARIABLE] [VALUE]\n\tSets env value.\n";

	write(STDOUT_FILENO, output, _strlen(output));
	output = "\tIf the specified VARIABLE exists, its value will be updated.\n";
	write(STDOUT_FILENO, output, _strlen(output));
	output = "\tIf the VARIABLE does not exist, create new env.\n\n";
	write(STDOUT_FILENO, output, _strlen(output));
	output = "\tIf the command fails, print error messages to stderr.\n";
	write(STDOUT_FILENO, output, _strlen(output));
}

/**
 * displayUnsetenvHelp - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void displayUnsetenvHelp(void)
{
	char *output = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an env.\n";

	write(STDOUT_FILENO, output, _strlen(output));
	output = "\tSpecify the VARIABLE to be removed from the environment.\n\n";
	write(STDOUT_FILENO, output, _strlen(output));
	output = "\tIf the command fails, print error messages to stderr.\n";
	write(STDOUT_FILENO, output, _strlen(output));
}
