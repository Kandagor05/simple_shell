#include "shell.h"
/**
 * get_environ - this returns string array of environ
 * @info: contains potential arguments
 * Return: always 0 for success
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - deletes environ var
 * @info: contains potential arguments
 * Return: return 1 on delete, 0 otherwise
 * @var: var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t g = 0;
	char *n;

	if (!node || !var)
		return (0);

	while (node)
	{
		n = starts_with(node->str, var);
		if (n && *n == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), g);
			g = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		g++;
	}
	return (info->env_changed);
}

/**
 * _setenv - initializes new environ
 * @info: contains potential arguments
 * @var: var property
 * @value: environ value
 *  Return: always 0 for success
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *n;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		n = starts_with(node->str, var);
		if (n && *n == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
