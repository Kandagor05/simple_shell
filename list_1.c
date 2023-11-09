#include "shell.h"

/**
 * list_len - finds length
 * @y: pointer to node
 * Return: capacity
 */
size_t list_len(const list_t *y)
{
	size_t x = 0;

	while (y)
	{
		y = y->next;
		x++;
	}
	return (x);
}

/**
 * list_to_strings - array of strings returned
 * @head: pointer to node
 * Return: string arrays
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t x = list_len(head), w;
	char **strs;
	char *str;

	if (!head || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (w = 0; w < x; w++)
				free(strs[w]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}


/**
 * print_list - elements printed
 * @y: pointernode
 * Return: list capacity
 */
size_t print_list(const list_t *y)
{
	size_t x = 0;

	while (y)
	{
		_puts(convert_number(y->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(y->str ? y->str : "(nil)");
		_puts("\n");
		y = y->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - node returned  with prefix
 * @node: head pointer
 * @prefix: string  match
 * @v: next char
 * Return: void or match
 */
list_t *node_starts_with(list_t *node, char *prefix, char v)
{
	char *n = NULL;

	while (node)
	{
		n = starts_with(node->str, prefix);
		if (n && ((v == -1) || (*n == v)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets node index
 * @head: head pointer
 * @node: node pointer
 * Return: -1 or index node
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}
