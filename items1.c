#include "header.h"
/**
 * len_of_list - determines length of linked list
 * @header: this pointer acts as the first node
 *
 * Return: List size
 */
size_t len_of_list(const list_t *header)
{
	size_t a = 0;

	while (header)
	{
		header = header->next;
		a++;
	}
	return (a);
}

/**
 * stringlist - an array of stringlist
 * @header: pointer to first node
 *
 * Return: array of strings
 */
char **stringlist(list_t *header)
{
	list_t *node = header;
	size_t a = list_len(header), b;
	char **strs;
	char *str;

	if (!header || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; j < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_all_list - this function prints all elements of list_t linked list
 * @n: first node pointer
 *
 * Return: list size
 */
size_t print_all_list(const list_t *n)
{
	size_t a = 0;

	while (n)
	{
		_puts(convert_number(n->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(n->str ? n->str : "(nil)");
		_puts("\n");
		n = n->next;
		a++;
	}
	return (a);
}

/**
 * cstarting_node - the node which returns the initial prefix
 * @n: list head pointer
 * @refix: string to match
 * @b: the next character after prefix to match
 *
 * Return: null
 */
list_t *starting_node(list_t *n, char *refix, char b)
{
	char *p = NULL;

	while (n)
	{
		p = starts_with(n->str, refix);
		if (p && ((b == -1) || (*p == b)))
			return (n);
		n = n->next;
	}
	return (NULL);
}

/**
 * cratex - node index
 * @header: pointer to list head
 * @node: node pointer
 *
 * Return: index of node or -1
 */
ssize_t cratex(list_t *header, list_t *node)
{
	size_t a = 0;

	while (header)

	{
		if (header == node)
			return (a);
		header = header->next;
		a++;
	}
	return (-1);
}
