#include "shell.h"

/**
 * _erratoi - Converts a string to an integer with error handling.
 * @s: The input string to convert.
 *
 * Return: The integer value of the converted string or -1 on error.
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
	{
		s++; /* TODO: Investigate why this makes main return 255*/
	}

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
	}

	return (result);
}

/**
 * print_error - Prints an error message to stderr.
 * @info: Pointer to the info structure containing relevant information.
 * @estr: The error message string.
 */
void print_error(info_t *info, char *estr)
{
	_puts(info->fname);
	_puts(": ");
	print_d(info->line_count, STDERR_FILENO);
	_puts(": ");
	_puts(info->argv[0]);
	_puts(": ");
	_puts(estr);
}

/**
 * print_d - Prints an integer to a file descriptor.
 * @input: The integer to be printed.
 * @fd: The file descriptor to print to.
 *
 * Return: The number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
	{
		__putchar = _putchar;
	}

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
	{
		_abs_ = input;
	}

	current = _abs_;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}

	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Convert number to a string
 * @num: The number to be converted.
 * @base: The base for the conversion.
 * @flags: Conversion flags.
 *
 * Return: A pointer to the string representation of the converted number.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
	{
		*--ptr = sign;
	}

	return (ptr);
}

/**
 * remove_comments - Removes comments from a string.
 * @buf: The input string containing comments.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
