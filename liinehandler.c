#include "shell.h"

/**
 * lineHandler - Partitions a line lineLen from standard input as needed.
 * @line: A pointer to a line lineLen from standard input.
 * @lineLen: The length of line.
 */
void lineHandler(char **line, ssize_t lineLen)
{
	char *ol, *nl;
	char prev, current, next;
	size_t i, j;
	ssize_t newLen;

	newLen = grabNewLen(*line);
	if (newLen == lineLen - 1)
		return;
	nl = malloc(newLen + 1);
	if (!nl)
		return;
	j = 0;
	ol = *line;
	for (i = 0; ol[i]; i++)
	{
		current = ol[i];
		next = ol[i + 1];
		if (i != 0)
		{
			prev = ol[i - 1];
			if (current == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					nl[j++] = ' ';
					nl[j++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					nl[j++] = ';';
					nl[j++] = ' ';
					continue;
				}
				if (prev != ' ')
					nl[j++] = ' ';
				nl[j++] = ';';
				if (next != ' ')
					nl[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && prev != ' ')
					nl[j++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					nl[j++] = '&';
					nl[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && prev != ' ')
					nl[j++]  = ' ';
				else if (prev == '|' && next != ' ')
				{
					nl[j++] = '|';
					nl[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && ol[i - 1] != ' ')
				nl[j++] = ' ';
			nl[j++] = ';';
			if (next != ' ' && next != ';')
				nl[j++] = ' ';
			continue;
		}
		nl[j++] = ol[i];
	}
	nl[j] = '\0';

	free(*line);
	*line = nl;
}

/**
 * grabNewLen - This gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 * Return: The new length of the line.
 */

ssize_t grabNewLen(char *line)
{
	size_t i;
	ssize_t newLen = 0;
	char current, next;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next = line[i + 1];
		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					newLen += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					newLen += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					newLen++;
				if (next != ' ')
					newLen++;
			}
			else
				handleLogicalOperator(&line[i], &newLen);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				newLen++;
			if (next != ' ' && next != ';')
				newLen++;
		}
		newLen++;
	}
	return (newLen);
}
