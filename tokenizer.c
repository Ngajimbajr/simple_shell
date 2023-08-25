#include "shell.h"


/**
 * custom_strtow - Split a string into an array of words based on a delimiter.
 * @str: The input string to be split.
 * @d: The delimiter string used for splitting.
 *
 * Return: An array of dynamically allocated strings containing the split words
 *         NULL is returned if input is NULL, empty, or memory allocation fails
 */
char **custom_strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	/* If delimiter is not provided, use a space as the default delimiter*/
	if (!d)
		d = " ";

	/* Count the number of words in the input string*/
	for (i = 0; str[i] != '\0'; i++)
	{
		if (!isDelim(str[i], d) && (isDelim(str[i + 1], d) || !str[i + 1]))
			numwords++;
	}

	/* Handle case when there are no words*/
	if (numwords == 0)
		return (NULL);

	/* Allocate memory for the array of strings*/
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	/* Split the input string into words*/
	for (i = 0, j = 0; j < numwords; j++)
	{
		/* Skip leading delimiters*/
		while (isDelim(str[i], d))
			i++;

		/* Count characters in the current word*/
		k = 0;
		while (!isDelim(str[i + k], d) && str[i + k])
			k++;

		/*Allocate memory for the word and copy characters*/
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			/*Clean up and return NULL on memory allocation failure*/
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		/*Copy characters from input string to the word*/
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}

	s[j] = NULL; /* Null-terminate the array of strings*/
	return (s);
}

/**
 * custom_strtow2 - Splits a string into words based on a delimiter
 * @str: The input string
 * @d: The delimiter character
 *
 * Return: an array of strings containing the words from the input string
 * separated by the given delimiter. Returns NULL if memory allocation fails
 * or if there are no words in the input string.
 */
char **custom_strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	/* Count the number of words in the input string*/
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	}

	/* Handle case when there are no words*/
	if (numwords == 0)
		return (NULL);

	/* Allocate memory for the array of strings*/
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	/* Split the input string into words*/
	for (i = 0, j = 0; j < numwords; j++)
	{
		/* Skip leading delimiter*/
		while (str[i] == d && str[i] != d)
			i++;

		/* Count characters in the current word*/
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;

		/* Allocate memory for the word and copy characters*/
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			/* Clean up and return NULL on memory allocation failure*/
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		/* Copy characters from input string to the word*/
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}

	s[j] = NULL;/* Null-terminate the array of strings*/
	return (s);
}
