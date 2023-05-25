#include <stdio.h>
#include <ctype.h>

void rot13String(char *str);
char rot13(char c);

/**
 * main - prompts user for string
 * Return: on Success return 0
 */
int main(void)
{
char input[100];
printf("Enter a string: ");
fgets(input, sizeof(input), stdin);
rot13String(input);
printf("The encoded rot13 string is: %s", input);
return (0);
}

/**
 * rot13 - A function that takes a character
 *         and rotates it 13 times.
 * @c: This is the input char
 * Return: The rotated character
 */
char rot13(char c)
{
if (isalpha(c))
{
if (c >= 'a' && c <= 'm')
{
c += 13;
}
else if (c >= 'A' && c <= 'M')
{
c += 13;
}
else if (c >= 'n' && c <= 'z')
{
c -= 13;
}
else if (c >= 'N' && c <= 'Z')
{
c -= 13;
}
}
return (c);
}

/**
 * rot13String - Takes a string and applies rot13 function
 *                to each character in the string
 * @str: This is a pointer that points to the
 *       characters in memory
 */
void rot13String(char *str)
{
while (*str)
{
*str = rot13(*str);
str++;
}
}
