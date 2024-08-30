#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @s: The string.
 *
 * Return: The length of the string, or 0 if s is NULL.
 */
int _strlen(char *s)
{
    int length = 0;

    if (s == NULL)
        return 0;

    while (s[length])
        length++;

    return length;
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: An integer less than, equal to, or greater than zero, if s1 is
 *         less than, equal to, or greater than s2.
 */
int _strcmp(char *s1, char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return -1; // Indicate an error if any string is NULL

    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: The concatenated string, or NULL if either pointer is NULL.
 */
char *_strcat(char *dest, char *src)
{
    char *ptr;

    if (dest == NULL || src == NULL)
        return NULL; // Indicate an error if any string is NULL

    ptr = dest + _strlen(dest);

    while (*src)
        *ptr++ = *src++;

    *ptr = '\0';
    return dest;
}

/**
 * _strcpy - Copies a string.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: The destination buffer, or NULL if either pointer is NULL.
 */
char *_strcpy(char *dest, char *src)
{
    char *ptr;

    if (dest == NULL || src == NULL)
        return NULL; // Indicate an error if any string is NULL

    ptr = dest;

    while ((*ptr++ = *src++) != '\0')
        ;

    return dest;
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string, or NULL on failure.
 */
char *_strdup(const char *str)
{
    char *dup;
    size_t len;

    if (str == NULL)
        return NULL; // Return NULL if the input string is NULL

    len = _strlen((char *)str);
    dup = malloc(len + 1);

    if (dup == NULL)
    {
        perror("malloc failed"); // Print error if malloc fails
        return NULL;
    }

    _strcpy(dup, (char *)str);
    return dup;
}

/**
 * _puts - Prints a string to stdout.
 * @str: The string to print.
 *
 * Return: 0 on success, -1 on error.
 */
int _puts(char *str)
{
    if (str == NULL)
        return -1; // Return -1 if the string is NULL

    if (write(STDOUT_FILENO, str, _strlen(str)) == -1)
        return -1; // Return -1 if write fails

    return 0;
}

/**
 * _putchar - Writes a single character to stdout.
 * @c: The character to write.
 *
 * Return: On success, 1 is returned. On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    if (write(STDOUT_FILENO, &c, 1) == -1)
        return -1; // Return -1 if write fails

    return 1;
}

