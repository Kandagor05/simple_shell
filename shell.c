#include "shell.h"
/**
 * interactive - checks for interactive mode
 * @info: structure address
 * Return: 1 for interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks for delimeter
 * @v: character to check
 * @delim: del string
 * Return: 1 if true, and 0 if false
 */
int is_delim(char v, char *delim)
{
	while (*delim)
		if (*delim++ == v)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic char
 * @v: input char
 * Return: 1 for v is alphabetic, and 0 otherwise
 */

int _isalpha(int v)
{
	if ((v >= 'a' && v <= 'z') || (v >= 'A' && v <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - changes string to int
 * @w: string to change
 * Return: 0 for no numbers, otherwise change
 */

int _atoi(char *w)
{
	int x, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (x = 0; w[x] != '\0' && flag != 2; x++)
	{
		if (w[x] == '-')
			sign *= -1;

		if (w[x] >= '0' && w[x] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (w[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
