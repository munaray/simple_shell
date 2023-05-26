#include "shell.h"

/**
 * handleLogicalOperator - This checks a line for logical
 * operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @newLen: A pointer to newLen in grabNewLen().
 */
void handleLogicalOperator(char *line, ssize_t *newLen)
{
	char prev, current, next;

	prev = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && prev != ' ')
			(*newLen)++;
		else if (prev == '&' && next != ' ')
			(*newLen)++;
	}
	else if (current == '|')
	{
		if (next == '|' && prev != ' ')
			(*newLen)++;
		else if (prev == '|' && next != ' ')
			(*newLen)++;
	}
}
