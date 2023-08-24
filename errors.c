#include "shell.h"

/**
 * printString - Prints a null-terminated string
 * @str: The string to be printed
 *
 * This function takes a null-terminated string and prints it using
 * the _putChar function.
 */
void printString(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		printChar(str[index]);
		index++;
	}
}

/**
 * printChar - Writes a character to stderr
 * @c: The character to be printed
 *
 * This function writes a character to the stderr stream. It uses a buffer
 * to optimize writing and flushes the buffer when necessary.
 *
 * Return:On success, 1 On error, 1 is returned and errno is set appropriately.
 */
int printChar(char c)
{
	static int currentIndex;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || currentIndex >= WRITE_BUF_SIZE)
	{
		write(2, buffer, currentIndex);
		currentIndex = 0;
	}

	if (c != BUF_FLUSH)
		buffer[currentIndex++] = c;

	return (1);
}

/**
 * printCharToFileDescriptor - Writes a character to the given file descriptor
 * @c: The character to be printed
 * @fd: The file descriptor to write to
 *
 * This function writes a character to the provided file descriptor. It uses a
 * buffer to optimize writing and flushes the buffer when necessary.
 *
 * Return:On success, 1,On error,-1 is returned and errno is set appropriately.
 */
int printCharToFileDescriptor(char c, int fd)
{
	static int currentIndex;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || currentIndex >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, currentIndex);
		currentIndex = 0;
	}

	if (c != BUF_FLUSH)
		buffer[currentIndex++] = c;

	return (1);
}

/**
 * printStringToFileDescriptor - Prints a null-terminated string to a file.
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 *
 * This function takes a null-terminated string and prints it to the provided
 * file descriptor using the printCharToFileDescriptor function.
 *
 * Return: The number of characters written.
 */
int printStringToFileDescriptor(char *str, int fd)
{
	int charsWritten = 0;

	if (!str)
		return (0);

	while (*str)
	{
		charsWritten += printCharToFileDescriptor(*str++, fd);
	}

	return (charsWritten);
}
