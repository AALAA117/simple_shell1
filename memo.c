#include "shell.h"
/**
 * memory_handler - free memory
 * @signum: signal
 * @buff:..
 * Return: nothing
 */
void memory_handler(int signum, char **buff);
void memory_handler(int __attribute__((unused))signum, char **buff)
{
	if (*buff != NULL)
	{
		free(*buff);
		*buff = NULL;
	}
	exit(EXIT_SUCCESS);
}
