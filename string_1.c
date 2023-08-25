#include "shell.h"

/**
 * _strcpy - Copies a string to another
 * @dest: The destination string
 * @src: The source string
 *
 * Return: A pointer to the destination string
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	/* Check for self-copy or NULL source*/
	if (dest == src || src == 0)
		return (dest);

	/*Copy characters until null-terminator*/
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}

	/* Add null-terminator to the destination*/
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: The string to be duplicated
 *
 * Return: On success,pointer to duplicated string.On error,NULL is returned
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	/* Handle NULL input*/
	if (str == NULL)
		return (NULL);

	/* Calculate the length of the string*/
	while (*str++)
		length++;

	/* Allocate memory for the duplicated string*/
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	/* Copy characters in reverse order*/
	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * _puts - Prints a string to the standard output
 * @str: The string to be printed
 *
 * Return: None
 */
void _puts(char *str)
{
	int i = 0;

	/* Check for NULL input*/
	if (!str)
		return;

	/* Print characters until null-terminator*/
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Writes a character to the standard output
 * @c: The character to be written
 *
 * Return: On success, 1. On error, -1 is returned,errno is set appropriately
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];


	/* Flush buffer if necessary or if buffer size is exceeded*/
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	/* Store character in buffer if not flushing*/
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}
