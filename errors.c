#include "shell.h"

/**
 * _eputs -Func. that outputs an input str.
 *
 * @str: String to be printed by the function.
 *
 * Return: Returns Nothing.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - This func. writes the char c to the stderr.
 *
 * @c: The character to be written to the stderr.
 *
 * Return: Returns 1 On success, else
 * returns -1 on error, and errno is set accordingly..
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given file descriptor.
 *
 * @c: The char to be printed.
 *
 * @fd: The filedescriptor.
 *
 * Return: On success, returns 1, and
 * On error, returns -1 is returned printing the errno.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - Func. thst prints an input str.
 *
 * @str: The string to be printed.
 *
 * @fd: the filedescriptor.
 *
 * Return: Returns the number of chararaters to put.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
