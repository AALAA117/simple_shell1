#include "shell.h"

/**
 * _strlen - calculate the length of string
 * @s: argument string
 * Return: length of given string
 */

int _strlen(char *s)
{
int count = 0;
while (*(s + count) != '\0')
{
count++;
}
return (count);
}

/**
 * _strcpy - copies the string to destination string
 * @dest: destination string
 * @src: source string
 * Return: destination string
 */

char *_strcpy(char *dest, char *src)
{
int j, i = 0;
while (src[i] != '\0')
{
i++;
}
for (j = 0; j <= i; j++)
{
dest[j] = src[j];
}
dest[j] = '\0';
return (dest);
}

/**
 * _strcat - concatenates two strings
 * @dest: argument string
 * @src: argument string
 * Return: concatenated string
 */

char *_strcat(char *dest, char *src)
{
int i = 0;
int dest_length = 0;
while (dest[dest_length] != '\0')
{
dest_length++;
}
while (src[i] != '\0')
{
dest[dest_length + i] = src[i];
i++;
}
dest[dest_length + i] = '\0';
return (dest);
}

/**
 * starts_with - checks if str2 starts with str1
 * @str1: string to search
 * @str2: the substring to find
 *
 * Return: address of next char of str1 or NULL
 */
char *starts_with(const char *str1, const char *str2)
{
	while (*str2)
		if (*str2++ != *str1++)
			return (NULL);
	return ((char *)str1);
}
