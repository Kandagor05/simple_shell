#include "shell.h"
/**
 * is_chain - tests chain delimeter
 * @info:  par struct
 * @buf: char buffer
 * @n: address of buf
 *
 * Return: Success 1, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *n)
{
	size_t w = *n;

	if (buf[w] == '|' && buf[w + 1] == '|')
	{
		buf[w] = 0;
		w++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[w] == '&' && buf[w + 1] == '&')
	{
		buf[w] = 0;
		w++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[w] == ';') /* found end  command */
	{
		buf[w] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*n = w;
	return (1);
}

/**
 * check_chain - entry point checker
 * @info: parameter Strct
 * @buf: buffer
 * @n: position address
 * @g: start
 * @len: length
 * Return: Null
 */
void check_chain(info_t *info, char *buf, size_t *n, size_t g, size_t len)
{
	size_t w = *n;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[g] = 0;
			w = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[g] = 0;
			w = len;
		}
	}

	*n = w;
}

/**
 * replace_alias - replaces aliases
 * @info:  parameter strct
 * Return: if replaced return 1, else 0
 */
int replace_alias(info_t *info)
{
	int x;
	list_t *node;
	char *n;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		n = _strchr(node->str, '=');
		if (!n)
			return (0);
		n = _strdup(n + 1);
		if (!n)
			return (0);
		info->argv[0] = n;
	}
	return (1);
}

/**
 * replace_vars - replaces vars
 * @info: parameter strct
 * Return: if replaced ruturn 1, else 0
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[x][1], '=');
		if (node)
		{
			replace_string(&(info->argv[x]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: old string
 * @new: new String
 * Return:once replaced  1, else 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
