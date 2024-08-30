#include "shell.h"

char *_strdup(const char *str)
{
    char *dup;
    size_t len;

    if (str == NULL)
        return NULL;

    len = _strlen(str) + 1;
    dup = malloc(len);
    if (dup == NULL)
        return NULL;

    _strcpy(dup, str);
    return dup;
}

int _strlen(const char *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;

    return len;
}

char *_strcpy(char *dest, const char *src)
{
    char *start = dest;

    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return start;
}

char *_strcat(char *dest, const char *src)
{
    char *start = dest;

    while (*dest)
        dest++;

    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return start;
}

