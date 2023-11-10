#include "shell.h"

/**
 * main - entry point
 * @sv: argument count
 * @sc: arg vec
 * Return: 0 for success 1 on error
 */
int main(int sv, char **sc)
{
	info_t info[] = { INFO_INIT };
	int fo = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fo)
			: "r" (fo));

	if (sv == 2)
	{
		fo = open(sc[1], O_RDONLY);
		if (fo == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(sc[0]);
				_eputs(": 0: Can't open ");
				_eputs(sc[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fo;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, sc);
	return (EXIT_SUCCESS);
}
