#include "shell.h"

/**
 **_strncpy - copy string
 *@dest: destination
 *@src: source
 *@p: size of character to copy
 *Return: concatenated strg
 */
char *_strncpy(char *dest, char *src, int p)
{
	int g, z;
	char *a = dest;

	g = 0;
	while (src[g] != '\0' && g < p - 1)
	{
		dest[g] = src[g];
		g++;
	}
	if (g < p)
	{
		z = g;
		while (z < p)
		{
			dest[z] = '\0';
			z++;
		}
	}
	return (a);
}

/**
 **_strncat - concatenates two strngs
 *@dest: 1st string
 *@src: 2nd string
 *@p: maximally used bytes
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int p)
{
	int x, z;
	char *a = dest;

	x = 0;
	z = 0;
	while (dest[x] != '\0')
		x++;
	while (src[z] != '\0' && z < p)
	{
		dest[x] = src[z];
		x++;
		z++;
	}
	if (z < p)
		dest[x] = '\0';
	return (p);
}

/**
 **_strchr - locates character
 *@a: parsed string
 *@v: char to look for
 *Return: (a) ptr to memory a
 */
char *_strchr(char *a, char v)
{
	do {
		if (*a == v)
			return (a);
	} while (*a++ != '\0');

	return (NULL);
}
