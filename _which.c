#include "shell.h"
/**
 * _which - which example
 * @command:..
 * Return: nothing
 */
char *_which(char *command);
char *_which(char *command)
{
	char *path = NULL;
	char *cpy_path;
	char *token;
	char *command_path = NULL;
	struct stat st;

	if (command == NULL)
	{
		return (NULL);
	}
	path = getenv("PATH");
	cpy_path = _strdup(path);
	if (cpy_path == NULL)
	{
		return (NULL);
	}
	if (stat(command, &st) == 0)
	{
		free(cpy_path);
		return (command);
	}
	token = strtok(cpy_path, ":");
	while (token != NULL)
	{
		command_path = malloc(_strlen(token) + _strlen(command) + 2);
		if (command_path == NULL)
		{
			free(cpy_path);
			return (NULL);
		}
		_strcpy(command_path, token);
		_strcat(command_path, "/");
		_strcat(command_path, command);
		if (stat(command_path, &st) == 0)
		{
			free(cpy_path);
			return (command_path);
		}
		free(command_path);
		token = strtok(NULL, ":");
	}
	free(cpy_path);
	return (NULL);
}
