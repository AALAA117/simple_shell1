#include "shell.h"
/**
 * main - entry point
 *
 * Return: 0
 */
int main(void);
int main(void)
{
	pid_t pid;
	char *buff = NULL;
	char *cpy_buff;
	size_t size = 0;
	ssize_t read;
	char *token;
	char *delim = " \n";
	int count, i, status, j, k;
	char **argv;
	char *env[] = {"HOME=/", "PATH=/bin", NULL};

	if (isatty(STDIN_FILENO))
	{

		write(1, "$ ", 2);
		while ((read = getline(&buff, &size, stdin)) != -1)
		{
			cpy_buff = _strdup(buff);
			if (cpy_buff == NULL)
			{
				perror("NO MEMORY ALLOCATED");
				return (-1);
			}
			token = strtok(cpy_buff, delim);
			count = 0;
			while (token != NULL)
			{
				count++;
				token = strtok(NULL, delim);
			}
			free(cpy_buff);
			cpy_buff = NULL;
			argv = malloc(sizeof(char *) * (count + 1));
			token = strtok(buff, delim);
			i = 0;
			while (token != NULL)
			{
				argv[i] = _strdup(token);
				if (argv[i] == NULL)
				{
					perror("NO MEMORY ALLOCATED");
					return (-1);
				}
				token = strtok(NULL, delim);
				i++;
			}
			argv[i] = NULL;
			if (_strcmp(argv[0], "exit") == 0)
				exit(0);
			if (_strcmp(argv[0], "env") == 0)
			{
				k = 0;
				while (environ[k])
				{
					_puts(environ[k++]);
					_puts("\n");
				}
			}
			free(buff);
			buff = NULL;
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(1);
			}
			else if (pid == 0)
			{
				if (argv[0] == NULL)
				{
					for (j = 0; j < i; j++)
					{
						free(argv[j]);
					}
					free(argv);
					exit(1);
				}
				if (execve(argv[0], argv, env) == -1)
				{
					perror("./shell");
					exit(1);
				}
				exit(0);
			}
			else
			{
				wait(&status);
				write(1, "$ ", 2);
				for (j = 0; j < i; j++)
				{
					free(argv[j]);
				}
				free(argv);
			}
		}
		free(buff);
	}
	else
	{
		while ((read = getline(&buff, &size, stdin)) != -1)
		{
			cpy_buff = _strdup(buff);
			if (cpy_buff == NULL)
			{
				perror("NO MEMORY ALLOCATED");
				return (-1);
			}
			token = strtok(cpy_buff, delim);
			count = 0;
			while (token != NULL)
			{
				count++;
				token = strtok(NULL, delim);
			}
			free(cpy_buff);
			cpy_buff = NULL;
			argv = malloc(sizeof(char *) * (count + 1));
			token = strtok(buff, delim);
			i = 0;
			while (token != NULL)
			{
				argv[i] = _strdup(token);
				if (argv[i] == NULL)
				{
					perror("NO MEMORY ALLOCATED");
					return (-1);
				}
				token = strtok(NULL, delim);
				i++;
			}
			argv[i] = NULL;
			if (_strcmp(argv[0], "exit") == 0)
				exit(0);
			if (_strcmp(argv[0], "env") == 0)
			{
				i = 0;
				while (environ[i])
				{
					_puts(environ[i++]);
					_puts("\n");
				}
			}
			free(buff);
			buff = NULL;
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(1);
			}
			else if (pid == 0)
			{
				if (argv[0] == NULL)
				{
					for (j = 0; j < i; j++)
					{
						free(argv[j]);
					}
					free(argv);
					exit(1);
				}
				if (execve(argv[0], argv, env) == -1)
				{
					perror("./shell");
					exit(1);
				}
				exit(0);
			}
			else
			{
				wait(&status);
				for (j = 0; j < i; j++)
				{
					free(argv[j]);
				}
				free(argv);
			}
		}
		free(buff);
	}
	return (0);
}
