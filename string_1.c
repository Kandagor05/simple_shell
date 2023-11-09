#include "shell.h"
/**
 * _strcpy - copy string
 * @dest: Destination
 * @src: Source
 * Return: des pointer
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		w++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - copies same string twice
 * @str: string duplicate
 * Return: duplicate string pointer
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - input printed
 * @str: string
 * Return: null
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - character v written
 * @v:  char to print
 * Return: 1 for success
 * -1 on error and errno is set correctly
 */
int _putchar(char v)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (v == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (v != BUF_FLUSH)
		buf[x++] = v;
	return (1);
}
