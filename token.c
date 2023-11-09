#include "shell.h"
/**
 * **strtow - puts string to words
 * @str: string input
 * @o: string delimiter
 * Return: pointer else NULL
 */

char **strtow(char *str, char *o)
{
	int x, w, b, p, numwords = 0;
	char **a;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!o)
		o = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], o) && (is_delim(str[x + 1], o) || !str[x + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	a = malloc((1 + numwords) * sizeof(char *));
	if (!a)
		return (NULL);
	for (x = 0, w = 0; w < numwords; w++)
	{
		while (is_delim(str[x], o))
			x++;
		b = 0;
		while (!is_delim(str[x + b], o) && str[x + b])
			b++;
		a[w] = malloc((b + 1) * sizeof(char));
		if (!a[w])
		{
			for (b = 0; b < w; b++)
				free(a[b]);
			free(a);
			return (NULL);
		}
		for (p = 0; p < b; p++)
			a[w][p] = str[x++];
		a[w][p] = 0;
	}
	a[w] = NULL;
	return (a);
}

/**
 * **strtow2 - changes string words
 * @str: string input
 * @o: delimeter
 * Return: pointer else NULL
 */
char **strtow2(char *str, char o)
{
	int g, z, b, p, numwords = 0;
	char **a;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (g = 0; str[g] != '\0'; g++)
		if ((str[g] != o && str[g + 1] == o) ||
				    (str[g] != o && !str[g + 1]) || str[g + 1] == o)
			numwords++;
	if (numwords == 0)
		return (NULL);
	a = malloc((1 + numwords) * sizeof(char *));
	if (!a)
		return (NULL);
	for (g = 0, z = 0; z < numwords; z++)
	{
		while (str[g] == o && str[g] != o)
			g++;
		b = 0;
		while (str[g + b] != o && str[g + b] && str[g + b] != o)
			b++;
		a[z] = malloc((b + 1) * sizeof(char));
		if (!a[z])
		{
			for (b = 0; b < z; b++)
				free(a[b]);
			free(a);
			return (NULL);
		}
		for (p = 0; p < b; p++)
			a[z][p] = str[g++];
		a[z][p] = 0;
	}
	a[z] = NULL;
	return (a);
}
