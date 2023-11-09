#include "shell.h"
/**
 * is_cmd - finds whether file is  executable
 * @info: information
 * @path: path
 * Return: success 1, else 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: path of string
 * @start: start
 * @stop: stop
 * Return: Buff new pointer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int x = 0, b = 0;

	for (b = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buf[b++] = pathstr[x];
	buf[b] = 0;
	return (buf);
}

/**
 * find_path - finds cmd in path
 * @info: information
 * @pathstr: path of string
 * @cmd: cmd to find
 * Return: cmd path for found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int x = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[w] || pathstr[x] == ':')
		{
			path = dup_chars(pathstr, curr_pos, x);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[x])
				break;
			curr_pos = x;
		}
		x++;
	}
	return (NULL);
}
