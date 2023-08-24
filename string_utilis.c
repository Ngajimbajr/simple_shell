#include "shell.h"

/**
 * isInteractive - Check if the shell is in interactive mode.
 *
 * @info: Address of struct info.
 *
 * Return: 1 if interactive mode, 0 otherwise.
 */
int isInteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - Check if a character is a delimiter.
 *
 * @c: Character to check.
 * @delim: Delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */
int isDelimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * isAlphabetic - Check if a character is alphabetic .
 *
 * @c: Character to check .
 *
 * Return: 1 if c is alphabetic , 0 otherwise .
 */
int isAlphabetic(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * stringToInteger - Convert a string to an integer .
 *
 * @s: String to be converted .
 *
 * Return: 0 if no numbers in string, converted number otherwise.
 */
int stringToInteger(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '_')
		{
			sign *= -1;
		}

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		} else if (flag == 1)
		{
			flag = 2;
		}
	}

	output = (sign == -1) ? -result : result;

	return (output);
}
