#include "shell.h"
/**
 * _strlen - length of string
 * @a: length to be checked
 * Return: string length interger
 */
int _strlen(char *a)
{
	int x = 0;

	if (!a)
		return (0);

	while (*a++)
		x++;
	return (x);
}

/**
 * _strcmp - compares strings
 * @a1: 1st strang
 * @a2: 2nd strang
 * Return:  Positive if a1 > a2, zero if a1 == a2 ,Negative if a1 < a2
 */
int _strcmp(char *a1, char *a2)
{
	while (*a1 && *a2)
	{
		if (*a1 != *a2)
			return (*a1 - *a2);
		a1++;
		a2++;
	}
	if (*a1 == *a2)
		return (0);
	else
		return (*a1 < *a2 ? -1 : 1);
}

/**
 * starts_with - finds whether needle starts with haystack
 * @haystack: search
 * @needle: substring
 * Return: next character  or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - two strings concanated
 * @dest: destination
 * @src: source
 * Return: pointer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
