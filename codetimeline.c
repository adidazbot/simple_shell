#include "header.h"

/**
 * history_file - function to fetch the history of a file
 * @detail: structure of parameters
 *
 * Return: string allocated to the history file
 */

char *history_file(info_t *detail)
{
	char *buffer, *sector;

	sector = _getenv(detail, "HOME=");
	if (!sector)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(sector) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, sector);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * display_history - this function appends existing files
 * @detail: the parameter structure
 *
 * Return: 1 on success, else -1
 */
int display_history(info_t *detail)
{
	ssize_t fildest;
	char *filename = history_file(detail);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fildest = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fildest == -1)
		return (-1);
	for (node = detail->history; node; node = node->next)
	{
		_putsfd(node->str, fildest);
		_putfd('\n', fildest);
	}
	_putfd(BUF_FLUSH, fildest);
	close(fildest);
	return (1);
}

/**
 * input_history - reads history from file
 * @detail: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int input_history(info_t *detail)
{
	int itr, first = 0, count = 0;
	ssize_t fildest, length, filesize = 0;
	struct stat s;
	char *buffer = NULL, *filename = history_file(detail);

	if (!filename)
		return (0);

	fildest = open(filename, O_RDONLY);
	free(filename);
	if (fildest == -1)
		return (0);
	if (!fstat(fildest, &s))
		filesize = s.st_size;
	if (filesize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (filesize + 1));
	if (!buffer)
		return (0);
	length = read(fildest, buffer, filesize);
	buffer[filesize] = 0;
	if (length <= 0)
		return (free(buffer), 0);
	close(fildest);
	for (itr = 0; itr < filesize; itr++)
		if (buffer[itr] == '\n')
		{
			buffer[itr] = 0;
			create_history_items(detail, buffer + first, count++);
			first = itr + 1;
		}
	if (first != itr)
		create_history_items(detail, buffer + first, count++);
	free(buffer);
	detail->histcount = count;
	while (detail->histcount-- >= HIST_MAX)
		delete_node_at_index(&(detail->history), 0);
	recount_history(detail);
	return (detail->histcount);
}

/**
 * create_history_items - adds entry to a history linked list
 * @detail: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @count: the history linecount, histcount
 *
 * Return: Always 0
 */
int create_history_items(info_t *detail, char *buffer, int count)
{
	list_t *node = NULL;

	if (detail->history)
		node = detail->history;
	add_node_end(&node, buffer, count);

	if (!detail->history)
		detail->history = node;
	return (0);
}

/**
 * recount_history - this function re enumarate the history
 * @detail: Structure containing potential arguments.
 *
 * Return: the new histcount
 */
int recount_history(info_t *detail)
{
	list_t *node = detail->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (detail->histcount = i);
}
