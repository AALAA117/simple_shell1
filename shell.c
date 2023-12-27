#include "shell.h"
/**
 * main - entry point
 * @ac:..
 * @av:..
 * Return: 0
 */
int main(int ac, char **av);
int main(int ac, char **av)
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

	signal(SIGINT, SIG_IGN);
	if (isatty(STDIN_FILENO))
	{
		write(1, "$ ", 2);
		while ((read = getline(&buff, &size, stdin)) != -1)
		{
			if (read > 1 && buff[read - 1] == '\n')
			{
				buff[read - 1] = '\0';
			}
			else
			{
				write(1, "$ ", 2);
				continue;
			}
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
					free(argv);
					free(buff);
					perror("NO MEMORY ALLOCATED");
					exit(EXIT_FAILURE);
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
					exit(EXIT_FAILURE);
				}
				exit(EXIT_SUCCESS);
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
		memory_handler(0, &buff);
	}
	else
	{
		if (ac < 1)
		{
			exit(EXIT_FAILURE);
		}
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
					write(STDOUT_FILENO, av[0], _strlen(av[0]));
					write(STDOUT_FILENO, ": 1: ", _strlen(": 1: "));
					write(STDOUT_FILENO, argv[0], _strlen(argv[0]));
					write(STDOUT_FILENO, ": not found\n", _strlen(": not found\n"));
					exit(EXIT_FAILURE);
				}
				exit(EXIT_SUCCESS);
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
	}
	return (0);
}
