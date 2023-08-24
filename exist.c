#include "shell.h"

// Function to copy a string
// Parameters:
// dest: the destination string to be copied to
// src: the source string
// n: the amount of characters to be copied
// Returns: the concatenated string
char *_strncpy(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;  // Store the starting address of destination

    i = 0;
    // Copy characters from source to destination until n characters or null terminator is reached
    while (src[i] != '\0' && i < n - 1)
    {
        dest[i] = src[i];
        i++;
    }
    // If the copy was shorter than n, fill the remaining with null characters
    if (i < n)
    {
        j = i;
        while (j < n)
        {
            dest[j] = '\0';
            j++;
        }
    }
    return (s);  // Return the starting address of the destination
}

// Function to concatenate two strings
// Parameters:
// dest: the first string
// src: the second string
// n: the amount of bytes to be maximally used
// Returns: the concatenated string
char *_strncat(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;  // Store the starting address of destination

    i = 0;
    j = 0;
    // Find the end of the destination string
    while (dest[i] != '\0')
        i++;
    // Copy characters from source to the end of destination until n characters or null terminator is reached
    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    // If the concatenation was shorter than n, append a null terminator
    if (j < n)
        dest[i] = '\0';
    return (s);  // Return the starting address of the destination
}

// Function to locate a character in a string
// Parameters:
// s: the string to be parsed
// c: the character to look for
// Returns: a pointer to the memory area s, or NULL if not found
char *_strchr(char *s, char c)
{
    do {
        if (*s == c)
            return (s);
    } while (*s++ != '\0');

    return (NULL);  // Return NULL if character is not found
}
