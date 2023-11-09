#include "shell.h"
/**
 * _memset - constant byte filled tomemory
 * @a: memory area pointer
 * @u: byte to fill *a with
 * @p: bytes quantity
 * Return: memory area a pointer
 */
char *_memset(char *a, char u, unsigned int p)
{
	unsigned int x;

	for (x = 0; x < p; x++)
		a[x] = u;
	return (a);
}

/**
 * ffree - frees all  strings
 * @nn: all strings
 */
void ffree(char **nn)
{
	char **s = nn;

	if (!nn)
		return;
	while (*nn)
		free(*nn++);
	free(s);
}

/**
 * _realloc - reallocates memory
 * @ptr: previous block pointer
 * @old_size: byte size
 * @new_size: byte of new block
 * Return: pointer to block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *n;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	n = malloc(new_size);
	if (!n)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		n[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (n);
}
