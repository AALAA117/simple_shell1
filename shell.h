#ifndef SHELL_H
#define SHELL_H
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
/* Global environemnt */
extern char **environ;
/*string functions*/
char *starts_with(const char *str1, const char *str2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int _putchar(char c);
void _puts(char *str);
char *_strdup(const char *str);
int _strcspn(const char *str1, const char *str2);
size_t _strspn(const char *str1, const char *str2);
char *_strtok(char *s1, const char *s2);
/*files functions*/
void read_file(const char *filename, char **arr[]);

/*shell functions*/
void memory_handler(int signum, char **buff);
char *_which(char *command);
#endif
