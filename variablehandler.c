#include "shell.h"

/**
 * replaceVariable - This is introduced to replace
 *					ariables in command arguments.
 * @line: A double pointer containing the command and arguments.
 * @retLastExeCmd: A pointer to the return value of the
 *				last executed command.
 */
void replaceVariable(char **line, int *retLastExeCmd)
{
	int j, k = 0, len;
	char *replacement = NULL, *ol = NULL, *nl;

	ol = *line;
	for (j = 0; ol[j]; j++)
	{
		if (ol[j] == '$' && ol[j + 1] &&
				ol[j + 1] != ' ')
		{
			if (ol[j + 1] == '$')
			{
				replacement = getPid();
				k = j + 2;
			}
			else if (ol[j + 1] == '?')
			{
				replacement = _itoa(*retLastExeCmd);
				k = j + 2;
			}
			else if (ol[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; ol[k] &&
						ol[k] != '$' &&
						ol[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = envValueHandler(&ol[j + 1], len);
			}
			nl = malloc(j + _strlen(replacement)
					  + _strlen(&ol[k]) + 1);
			if (!line)
				return;
			nl[0] = '\0';
			_strncat(nl, ol, j);
			if (replacement)
			{
				_strcat(nl, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(nl, &ol[k]);
			free(ol);
			*line = nl;
			ol = nl;
			j = -1;
		}
	}
}
