#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: pointer to the memory area
 * @b: byte to fill memory with
 * @n: number of bytes to be filled
 * 
 * Return: pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        s[i] = b;

    return s;
}

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to the previously allocated memory
 * @old_size: size of the old memory block
 * @new_size: size of the new memory block
 * 
 * Return: pointer to the newly allocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;
    char *old_ptr;
    unsigned int i;

    if (new_size == old_size)
        return ptr;

    if (ptr == NULL)
        return malloc(new_size);

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;

    old_ptr = ptr;
    for (i = 0; i < old_size && i < new_size; i++)
        new_ptr[i] = old_ptr[i];

    free(ptr);
    return new_ptr;
}

/**
 * ffree - frees a list of strings
 * @pp: pointer to the list of strings
 */
void ffree(char **pp)
{
    char **p = pp;

    if (!pp)
        return;

    while (*pp)
    {
        free(*pp);
        pp++;
    }
    free(p);
}

/**
 * bfree - frees a pointer and sets it to NULL
 * @ptr: pointer to the pointer to be freed
 * 
 * Return: 1 if freed, 0 otherwise
 */
int bfree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return 1;
    }
    return 0;
}

