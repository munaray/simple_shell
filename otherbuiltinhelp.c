#include "shell.h"

/**
 * displayAllHelp - Displays all possible builtin shellby commands.
 */
void displayAllHelp(void)
{
	char *output = "Shellby\nThese built-in commands are defined internally.\n";

    write(STDOUT_FILENO, output, _strlen(output));
    output = "Type 'help' to view this list.\nType 'help command' to find ";
    write(STDOUT_FILENO, output, _strlen(output));
    output = "out more about the 'command'.\n\n  alias   \t";
    write(STDOUT_FILENO, output, _strlen(output));
    output = "alias [NAME[='VALUE'] ...]\n  navigate    \tnavigate ";
    write(STDOUT_FILENO, output, _strlen(output));
    output = "[DIRECTORY]\n  terminate    \tterminate [STATUS]\n  env     \tenv";
    write(STDOUT_FILENO, output, _strlen(output));
    output = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
    write(STDOUT_FILENO, output, _strlen(output));
    output = "unsetenv [VARIABLE]\n";
    write(STDOUT_FILENO, output, _strlen(output));
}

/**
 * displayAliasHelp - Displays information on the builtin command 'alias'.
 */
void displayAliasHelp(void)
{
	char *output = "alias: alias [NAME[='VALUE'] ...]\n\tManage command aliases.\n";

	write(STDOUT_FILENO, output, _strlen(output));
	output = "\n\talias: Prints a list of all defined aliases, one per line, ";
	write(STDOUT_FILENO, output, _strlen(output));
	output = "in the format NAME='VALUE'.\n\talias name [name2 ...]: Prints";
	write(STDOUT_FILENO, output, _strlen(output));
	output = " the aliases 'name', 'name2', etc., one per line, in the ";
	write(STDOUT_FILENO, output, _strlen(output));
	output = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, output, _strlen(output));
	output = " or updates an alias for each 'NAME' with the provided 'VALUE'.";
	write(STDOUT_FILENO, output, _strlen(output));
	output = " If 'NAME' is already an alias, its value will be replaced.\n";
	write(STDOUT_FILENO, output, _strlen(output));
}

/**
 * displayCdHelp - Displays information on the shellby builtin command 'cd'.
 */
void displayCdHelp(void)
{
	char *output = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, output, _strlen(output));
	output = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, output, _strlen(output));
	output = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, output, _strlen(output));
	output = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, output, _strlen(output));
	output = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, output, _strlen(output));
	output = "after a change of directory.\n";
	write(STDOUT_FILENO, output, _strlen(output));
}

/**
 * displayExitHelp - Displays information on the shellby builtin command 'exit'.
 */
void displayExitHelp(void)
{
	char *output = "terminate: terminate [STATUS]\n\tTerminates the shell.\n\n\tThe ";

	write(STDOUT_FILENO, output, _strlen(output));
	output = "STATUS argument is the integer used to terminate the shell.";
	write(STDOUT_FILENO, output, _strlen(output));
	output = " If no argument is provided, the command is interpreted as";
	write(STDOUT_FILENO, output, _strlen(output));
	output = " terminate 0.\n";
	write(STDOUT_FILENO, output, _strlen(output));

}

/**
 * displayHelpMessage - Displays information on the shellby builtin command 'help'.
 */
void displayHelpMessage(void)
{
	char *output = "Guide: help\n\tView all available Shellby built-in functions.\n";
	write(STDOUT_FILENO, output, _strlen(output));
    output = "\n      help [FUNCTION NAME]\n\tView specific details about each ";
    write(STDOUT_FILENO, output, _strlen(output));
    output = "built-in function.\n";
    write(STDOUT_FILENO, output, _strlen(output));
}
