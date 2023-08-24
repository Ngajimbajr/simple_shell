#include "shell.h"

// Function to calculate the length of a string
// Input: s - the string whose length to check
// Output: Integer length of the string
int string_length(char *s) {
    int length = 0;

    if (!s) {
        return 0;
    }

    while (*s++) {
        length++;
    }

    return length;
}

// Function to perform lexicographic comparison of two strings
// Input: s1 - the first string
//        s2 - the second string
// Output: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
int string_compare(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) {
            return (*s1 - *s2);
        }
        s1++;
        s2++;
    }

    if (*s1 == *s2) {
        return 0;
    } else {
        return (*s1 < *s2 ? -1 : 1);
    }
}

// Function to check if a string starts with another string
// Input: haystack - string to search
//        needle - the substring to find
// Output: Address of next character of haystack or NULL
char *find_start(const char *haystack, const char *needle) {
    while (*needle) {
        if (*needle++ != *haystack++) {
            return NULL;
        }
    }
    return (char *)haystack;
}

// Function to concatenate two strings
// Input: dest - the destination buffer
//        src - the source buffer
// Output: Pointer to destination buffer
char *string_concat(char *dest, char *src) {
    char *result = dest;

    while (*dest) {
        dest++;
    }
    while (*src) {
        *dest++ = *src++;
    }
    *dest = *src;

    return result;
}
