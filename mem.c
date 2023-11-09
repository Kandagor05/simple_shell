#include "shell.h"
/**
 * bfree - pointer is freed and NULLs address
 * @ptr: pointer address to be freed
 * Return: success 1, else 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
