#include "shell.h"
/**
 * _strcspn - calculate the number of characters before the 1st occurrence
 * of character present in both the string.
 *@str1 : The Target string in which search has to be made.
 *@str2 : Argument string containing characters to match in target string.
 * Return: the number of characters before the 1st occurrence
 * of character present in both the string.
 */

int _strcspn(const char *str1, const char *str2)
{
int count = 0;
while (*str1 != '\0')
{
if (*str1 == *str2)
return (count);
str1++;
count++;
}
return (count);
}


/**
* _strspn - the number of characters in the initial segment of str1
*which consist only of characters from str2
*@str1 : string to be scanned.
*@str2 : string containing the
*characters to match.
* Return: number of bytes.
*/
size_t _strspn(const char *str1, const char *str2)
{
int count = 0;
while (*str1 != '\0')
{
while (*str2 != '\0')
{
if (*str1 == *str2)
{
count++;
}
str1++;
str2++;
}
str1++;
}
return (count);
}

/**
 * _strtok - find a pointer to the first character of a token
 * @s1: string is modified and broken into smaller strings (tokens)
 * @s2: string contains the delimiter characters.
 * These may vary from one call to another
 * Return: pointer to the first character of a token or
 * a null pointer if there is no token
 */
char *_strtok(char *s1, const char *s2)
{
static char *p;
if (s1 != NULL)
p = s1;
if (p == NULL)
return (NULL);
p += _strspn(p, s2);
if (*p == '\0')
{
p = NULL;
return (p);
}
else
{
char *start = p;
p += _strcspn(p, s2);
if (*p == '\0')
{
p = NULL;
}
else
{
*p++ = '\0';
}
return (start);
}
}
