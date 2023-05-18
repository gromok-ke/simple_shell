#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	/*Check if ptr is not NULL and the value it points to is not NULL*/
	if (ptr && *ptr)
	{
		free(*ptr);
		/*Set *ptr to NULL to avoid dangling pointer*/
		*ptr = NULL;
		return (1);
	}
	return (0);
}
