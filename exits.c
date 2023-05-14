#include "shell.h"

/**
 * _strncpy - Func to coppy a str.
 *
 * @dest: String to be copied.
 *
 * @src: The source str.
 *
 * @n: the total amount of chars to be copied.
 *
 * Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - This Func. concatenates 2 strs.
 *
 * @dest: the 1st string.
 *
 * @src: the 2nd string.
 *
 * @n: Amount of bytes to be used.
 *
 * Return: Returns the joined string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - This Func. locates a char in a str.
 *
 * @s: The str to be parsed.
 *
 * @c: The char to be looked for.
 *
 * Return: returns a pointer to the memory area of string @s.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
