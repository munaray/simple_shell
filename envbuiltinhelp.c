#include "shell.h"

/**
 * displayEnvHelp - Displays information on the shellby builtin command 'env'.
 */
void displayEnvHelp(void)
{
	char *output = "env: env\n\tDisplay the current environment variables.\n";

	write(STDOUT_FILENO, output, _strlen(output));
}

/**
 * displaySetenvHelp - Displays information on the shellby builtin command 'setenv'.
 */
void displaySetenvHelp(void)
{
	char *output = "setenv: setenv [VARIABLE] [VALUE]\n\tSets the value of an environment variable.\n";

	write(STDOUT_FILENO, output, _strlen(output));
	output = "\tIf the specified VARIABLE exists, its value will be updated.\n";
	write(STDOUT_FILENO, output, _strlen(output));
	output = "\tIf the VARIABLE does not exist, a new environment variable will be created.\n\n";
	write(STDOUT_FILENO, output, _strlen(output));
	output = "\tIf the command fails, an error message will be printed to stderr.\n";
	write(STDOUT_FILENO, output, _strlen(output));
}

/**
 * displayUnsetenvHelp - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void displayUnsetenvHelp(void)
{
	char *output = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an environment variable.\n";

	write(STDOUT_FILENO, output, _strlen(output));
	output = "\tSpecify the VARIABLE to be removed from the environment.\n\n";
	write(STDOUT_FILENO, output, _strlen(output));
	output = "\tIf the command fails, an error message will be printed to stderr.\n";
	write(STDOUT_FILENO, output, _strlen(output));
}
