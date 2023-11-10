#include "shell.h"
/**
 * _eputs - prints input
 * @str: string to be printed
 * Return: Null.
 */
void _eputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}

/**
 * _eputchar - puts character v to std error
 * @v: printed character
 * Return: 1 for success,-1 for error which is appropriately set
 */
int _eputchar(char v)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (v == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (v != BUF_FLUSH)
		buf[x++] = v;
	return (1);
}

/**
 * _putfd - puts chsrscter v to given fd
 * @v: printed char
 * @fd: file descriptor
 * Return: return 1 for success, -1 for error and set appropriately
 */
int _putfd(char v, int fd)
{
	static int g;
	static char buf[WRITE_BUF_SIZE];

	if (v == BUF_FLUSH || g >= WRITE_BUF_SIZE)
	{
		write(fd, buf, g);
		g = 0;
	}
	if (v != BUF_FLUSH)
		buf[g++] = v;
	return (1);
}

/**
 * _putsfd - print input string
 * @str:printed string
 * @fd: file descriptor
 * Return: no of put characters
 */
int _putsfd(char *str, int fd)
{
	int g = 0;

	if (!str)
		return (0);
	while (*str)
	{
		g += _putfd(*str++, fd);
	}
	return (g);
}
