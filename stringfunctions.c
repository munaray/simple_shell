#include "shell.h"

/**
 * _strlen - This returns the lenght of a string.
 * @str: A pointer to the characters string.
 * Return: return the lenght of the character string.
 */
int _strlen(const char *str)
{
	int len = 0;

	if (!str)
		return (len);
	for (len = 0; str[len]; len++)
		;
	return (len);
}

/**
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by dest.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: return the destination string pointer.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - This marge two string.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * Return: the destination string pointer.
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - marge two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 * Return: the destination string pointer.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
