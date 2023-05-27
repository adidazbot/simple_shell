#include "header.h"

/**
 * i_cmd - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Returns: 1 if the file is an executable command, 0 otherwise.
 */
int i_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;

	if (!path || stat(path, &st))
		return 0;
	
	if (st.st_mode & S_IFREG)
	{
		return 1;
	}
	
	return 0;
}

/**
 * dp_chars - Duplicates characters.
 * @path_s: The PATH string.
 * @start: Starting index.
 * @stp: Stopping index.
 *
 * Returns: Pointer to a new buffer.
 */
char *dp_chars(char *path_s, int start, int stp)
{
	static char buf[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stp; a++)
	{
		if (path_s[a] != ':')
			buf[b++] = path_s[a];
	}

	buf[b] = 0;

	return buf;
}

/**
 * find_path - Finds the given command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Returns: Full path of the command if found, or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return NULL;

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (i_cmd(info, cmd))
			return cmd;
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dp_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
		else
		{
			_strcat(path, "/");
			_strcat(path, cmd);
		}
	
		if (i_cmd(info, path))
			return path;

		if (!pathstr[i])
			break;

		curr_pos = i;
		}
		i++;
	}

	return NULL;
}
