#include "header.h"

/**
 * bfr - Frees a pointer and sets its address to NULL
 * @ptr: Address of the pointer to be freed
 *
 * Returns: 1 if the pointer was freed, otherwise 0
 */
int bfr(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);   // Deallocates the memory pointed to by the pointer
		*ptr = NULL;  // Sets the pointer's address to NULL
		return 1;
	}
	return 0;
}
