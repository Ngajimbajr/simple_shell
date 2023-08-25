#include "shell.h"

/**
 * _strncpy - Copies at most n characters from src to dest
 * @dest: Pointer to the destination buffer
 * @src: Pointer to the source buffer
 * @n: Maximum number of characters to copy
 *
 * Return: Pointer to the starting address of the destination buffer
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;/* Store the starting address of destination*/

	i = 0;
	/* Copy characters from source to destination until n characters*/
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
    /*If the copy was shorter than n, fill the remaining with null characters*/
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (s);/* Return the starting address of the destination*/
}

/**
 * _strncat - Concatenates at most n characters from src to dest
 * @dest: Pointer to the destination string
 * @src: Pointer to the source string
 * @n: Maximum number of characters to concatenate
 *
 * Return: Pointer to the starting address of the destination string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;/* Store the starting address of destination*/

	i = 0;
	j = 0;
	/*Find the end of the destination string*/
	while (dest[i] != '\0')
		i++;
	/* Copy characters from source to the end of destination until n characters*/
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
    /* If the concatenation was shorter than n, append a null terminator*/
	if (j < n)
		dest[i] = '\0';
	return (s);/* Return the starting address of the destination*/
}

/**
 * _strchr - Locates the first occurrence of a character in a string
 * @s: Pointer to the string
 * @c: Character to locate
 *
 * Return: Pointer to the first occurrence of the character in the string.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);/* Return NULL if character is not found*/
}
