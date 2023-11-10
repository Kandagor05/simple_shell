#include "shell.h"
/**
 * input_buf - input buff
 * @info: par structure
 * @buf:  address
 * @len:  address
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t d = 0;
	size_t len_n = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		d = getline(buf, &len_n, stdin);
#else
		d = _getline(info, buf, &len_n);
#endif
		if (d > 0)
		{
			if ((*buf)[d - 1] == '\n')
			{
				(*buf)[d - 1] = '\0'; /* remove trailing newline */
				d--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = d;
				info->cmd_buf = buf;
			}
		}
	}
	return (d);
}

/**
 * get_input - get line -newline
 * @info: par structure
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t g, z, len;
	ssize_t d = 0;
	char **buf_n = &(info->arg), *n;

	_putchar(BUF_FLUSH);
	d = input_buf(info, &buf, &len);
	if (d == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		z = g; /* init new iterator to current buf position */
		n = buf + g; /* get pointer for return */

		check_chain(info, buf, &z, g, len);
		while (z < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &z))
				break;
			z++;
		}

		g = z + 1; /* increment past nulled ';'' */
		if (g >= len) /* reached end of buffer? */
		{
			g = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_n = n; /* pass back pointer to current command position */
		return (_strlen(n)); /* return length of current command */
	}

	*buf_n = buf; /* else not a chain, pass back buffer from _getline() */
	return (d); /* return length of buffer from _getline() */
}

/**
 * read_buf - read buff
 * @info: par structure
 * @buf: buffer
 * @g: size
 * Return: d
 */
ssize_t read_buf(info_t *info, char *buf, size_t *g)
{
	ssize_t d = 0;

	if (*g)
		return (0);
	d = read(info->readfd, buf, READ_BUF_SIZE);
	if (d >= 0)
		*g = d;
	return (d);
}

/**
 * _getline - gets next line
 * @info: par structure
 * @ptr: pointer
 * @length: capacity of the preallocated pointer
 * Return: a
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t g, len;
	size_t e;
	ssize_t d = 0, a = 0;
	char *n = NULL, *new_n = NULL, *v;

	n = *ptr;
	if (n && length)
		a = *length;
	if (g == len)
		g = len = 0;

	d = read_buf(info, buf, &len);
	if (d == -1 || (d == 0 && len == 0))
		return (-1);

	v = _strchr(buf + g, '\n');
	e = v ? 1 + (unsigned int)(v - buf) : len;
	new_n = _realloc(n, a, a ? a + e : e + 1);
	if (!new_n) /* MALLOC FAILURE! */
		return (n ? free(n), -1 : -1);

	if (a)
		_strncat(new_n, buf + g, e - g);
	else
		_strncpy(new_n, buf + g, e - g + 1);

	a += e - g;
	g = e;
	n = new_n;

	if (length)
		*length = a;
	*ptr = n;
	return (a);
}

/**
 * sigintHandler - block ctrl-C
 * @sig_num: signal number
 * Return: null
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
