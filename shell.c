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

	char *buff = NULL;
	pid_t pid;
	char *cpy_buff = NULL;
	size_t size = 0;
	ssize_t read;
	char *token;
	char *delim = " \n";
	int count, i, status, j, k;
	char **argv = NULL;
	char *path = NULL;
    (void)ac;

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
		while ((read = getline(&buff, &size, stdin)) != -1)
		{
			buff[_strcspn(buff, "\n")] = '\0';
			if (buff[0] == '\0')
			{
				write(STDOUT_FILENO, "$ ", 2);
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
					perror("no memory allocated");
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
			path = _which(argv[0]);
			if (path == NULL)
			{
				exit(EXIT_FAILURE);
			}
			if (path != NULL)
			{
				pid = fork();
				if (pid == -1)
				{
					free(path);
					perror("fork");
					exit(1);
				}
				else if (pid == 0)
				{
					if (execve(path, argv, NULL) == -1)
					{
						perror("./hsh");
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
				write(STDOUT_FILENO, "$ ", 2);
			}
			else
			{

				continue;
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
                k = 0;
                while (environ[k]) 
				{
				_puts(environ[k++]);
				_puts("\n"); 
                }
			   }
			free(buff);
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
				if (execve(argv[0], argv, NULL) == -1)
				{
					if (errno == ENOENT)
					{
						write(STDERR_FILENO, av[0], _strlen(av[0]));
						write(STDERR_FILENO, ": 1: ", _strlen(": 1: "));
						write(STDERR_FILENO, argv[0], _strlen(argv[0]));
						write(STDERR_FILENO, ": not found\n", _strlen(": not found\n"));
						}
					exit(EXIT_FAILURE);
				}
				exit(EXIT_SUCCESS);
			}
			else
			{
				wait(NULL);
				for (j = 0; j < i; j++)
				{
					free(argv[j]);
				}
				free(argv);
			}
		}
		free(buff);
	}
	return (EXIT_SUCCESS);
}
