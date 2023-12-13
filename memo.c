#include "shell.h"
/**
 * memory_handler - free memory
 * @signum: signal
 * Return: nothing
 */
void memory_handler(int __attribute__((unused))signum);
void memory_handler(int __attribute__((unused))signum)
{
	exit(EXIT_SUCCESS);
}
