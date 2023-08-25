#include "shell.h"

/**
 * string_length - Calculates the length of a string.
 * @s: The input string.
 *
 * Return: The length of the string.
 */
int string_length(char *s)
{
	int length = 0;

	if (!s)
	{
		return (0);
	}

	while (*s++)
	{
		length++;
	}

	return (length);
}

/**
 * string_compare - Compares two strings.
 * @s1: The first input string.
 * @s2: The second input string.
 *
 * Return: An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or to be greater than s2.
 */
int string_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}

	if (*s1 == *s2)
	{
		return (0);
	}
	else
	{
		return (*s1 < *s2 ? -1 : 1);
	}
}

/**
 * find_start - Finds the starting position of a substring in a string.
 * @haystack: The string to search within.
 * @needle: The substring to find.
 *
 * Return: A pointer to the starting position of the substring in the string,
 *         or NULL if the substring is not found.
 */
char *find_start(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
		{
			return (NULL);
		}
	}
	return ((char *)haystack);
}

/**
 * string_concat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string to be appended.
 *
 * Return: A pointer to the destination string.
 */
char *string_concat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = *src;

	return (result);
}
