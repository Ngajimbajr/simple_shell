#include "shell.h"

/**
 * Copies the contents of one string to another.
 *
 * @param dest The destination string.
 * @param src The source string.
 * @return Pointer to the destination string.
 */
char *_strcpy(char *dest, char *src) {
    int i = 0;

    // Check for self-copy or NULL source
    if (dest == src || src == 0)
        return dest;

    // Copy characters until null-terminator
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }

    // Add null-terminator to the destination
    dest[i] = 0;
    return dest;
}

/**
 * Duplicates a given string.
 *
 * @param str The string to duplicate.
 * @return Pointer to the duplicated string.
 */
char *_strdup(const char *str) {
    int length = 0;
    char *ret;

    // Handle NULL input
    if (str == NULL)
        return NULL;

    // Calculate the length of the string
    while (*str++)
        length++;

    // Allocate memory for the duplicated string
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return NULL;

    // Copy characters in reverse order
    for (length++; length--;)
        ret[length] = *--str;

    return ret;
}

/**
 * Prints a given string to the standard output.
 *
 * @param str The string to be printed.
 * @return Nothing.
 */
void _puts(char *str) {
    int i = 0;

    // Check for NULL input
    if (!str)
        return;

    // Print characters until null-terminator
    while (str[i] != '\0') {
        _putchar(str[i]);
        i++;
    }
}

/**
 * Writes a character to the standard output.
 *
 * @param c The character to print.
 * @return On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c) {
    static int i;
    static char buf[WRITE_BUF_SIZE];

    // Flush buffer if necessary or if buffer size is exceeded
    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        write(1, buf, i);
        i = 0;
    }

    // Store character in buffer if not flushing
    if (c != BUF_FLUSH)
        buf[i++] = c;

    return 1;
}
