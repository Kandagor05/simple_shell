#include "shell.h"

/**
 * _erratoi - changes string to int
 * @a: string to change
 * Return: 0 for no numbers -1 for conveted num
 */
int _erratoi(char *a)
{
	int g = 0;
	unsigned long int result = 0;

	if (*a == '+')
		a++;  /* TODO: why does this make main return 255? */
	for (g = 0;  a[g] != '\0'; g++)
	{
		if (a[g] >= '0' && a[g] <= '9')
		{
			result *= 10;
			result += (a[g] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints error messages
 * @info: info parameter and return
 * @estr: specified errors contained
 * Return: no num 0, converted num -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - print decimals numbers with base 10
 * @input: input
 * @fd: file descriptor
 * Return: number of characcters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int g, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (g = 1000000000; g > 1; g /= 10)
	{
		if (_abs_ / g)
		{
			__putchar('0' + current / g);
			count++;
		}
		current %= g;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter funct
 * @num: number
 * @base: base
 * @flags: arg flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long p = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		p = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[p % base];
		p /= base;
	} while (p != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - puts first instance of '#' with '\0'
 * @buf: modified string address
 * Return: always 0 for success
 */
void remove_comments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
