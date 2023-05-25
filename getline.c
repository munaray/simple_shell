#include "shell.h"

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: A pointer to the memory previously allocated.
 * @oldSize: The size in bytes of the allocated space for ptr.
 * @newSize: The size in bytes for the new memory block.
 *
 * Return: If newSize == oldSize - ptr.
 *         If newSize == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	void *mem;
	char *copyPtr, *filler;
	unsigned int i;

	if (newSize == oldSize)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(newSize);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (newSize == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	copyPtr = ptr;
	mem = malloc(sizeof(*copyPtr) * newSize);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = mem;

	for (i = 0; i < oldSize && i < newSize; i++)
		filler[i] = *copyPtr++;

	free(ptr);
	return (mem);
}

/**
 * allocateLineptr - Reassigns the lineptr variable for _getline.
 * @lineptr: A buffer to store an input string.
 * @lineptrSize: The size of lineptr.
 * @buffer: The string to assign to lineptr.
 * @bufferSize: The size of buffer.
 */
void allocateLineptr(char **lineptr, size_t *lineptrSize, char *buffer, size_t bufferSize)
{
	if (*lineptr == NULL)
	{
		if (bufferSize > 120)
			*lineptrSize = bufferSize;
		else
			*lineptrSize = 120;
		*lineptr = buffer;
	}
	else if (*lineptrSize < bufferSize)
	{
		if (bufferSize > 120)
			*lineptrSize = bufferSize;
		else
			*lineptrSize = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Reads input from a file.
 * @lineptr: A buffer to store the input.
 * @lineptrSize: The size of lineptr.
 * @file: The file to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **lineptr, size_t *lineptrSize, FILE *file)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(file);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	allocateLineptr(lineptr, lineptrSize, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
