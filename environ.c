#include "shell.h"

/**
 * _myenv - print environ
 * @info: contains potential arguments
 * Return: always 0 for success
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets value of environ
 * @info: contains potential arguments
 * @name: environ name
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *n;

	while (node)
	{
		n = starts_with(node->str, name);
		if (n && *n)
			return (n);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - new environ initialized
 * @info: contains potential arguments
 *  Return: always 0 for success
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - deletes environ
 * @info: contains potential arguments
 * Return: always 0 for success
 */
int _myunsetenv(info_t *info)
{
	int g;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (g = 1; g <= info->argc; g++)
		_unsetenv(info, info->argv[g]);

	return (0);
}

/**
 * populate_env_list - populates environ list
 * @info: contains potential arguments
 * Return: always 0 for  success
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t g;

	for (g = 0; environ[g]; g++)
		add_node_end(&node, environ[g], 0);
	info->env = node;
	return (0);
}
