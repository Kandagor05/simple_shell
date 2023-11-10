#include "shell.h"
/**
 * _myhistory - displays history list and one command by line
 * @info: contains potential arguments
 *  Return: always 0 success
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - alias set
 * @info: parameter structure
 * @str: string alias
 * Return: Always 0 for Success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *n, v;
	int ret;

	n = _strchr(str, '=');
	if (!n)
		return (1);
	v = *n;
	*n = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*n = v;
	return (ret);
}

/**
 * set_alias - alias set
 * @info: parameter structure
 * @str: string alias
 * Return: always 0 for success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *n;

	n = _strchr(str, '=');
	if (!n)
		return (1);
	if (!*++n)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - alias printed
 * @node: alias node
 * Return: always 0 for success, 1 on error
 */
int print_alias(list_t *node)
{
	char *n = NULL, *s = NULL;

	if (node)
	{
		n = _strchr(node->str, '=');
		for (s = node->str; s <= n; s++)
		_putchar(*s);
		_putchar('\'');
		_puts(n + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimic alias
 * @info: contains potential arguments
 *  Return: always 0 for Success
 */
int _myalias(info_t *info)
{
	int g = 0;
	char *n = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (g = 1; info->argv[g]; g++)
	{
		n = _strchr(info->argv[g], '=');
		if (n)
			set_alias(info, info->argv[g]);
		else
			print_alias(node_starts_with(info->alias, info->argv[g], '='));
	}

	return (0);
}
