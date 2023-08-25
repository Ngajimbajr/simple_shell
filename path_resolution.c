#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: Pointer to info_t struct (unused).
 * @path: Path of the file to check.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	/* Check if the path is valid and retrieve file stats */
	if (!path || stat(path, &st))
		return (0);

	/* Check if the file is a regular file */
	if (st.st_mode & S_IFREG)
		return (1);

	return (0);
}

/**
 * dup_chars - Duplicates characters from a string into a new buffer.
 * @pathstr: Source string.
 * @start: Starting index for duplication.
 * @stop: Stopping index for duplication.
 *
 * Return: Pointer to the new buffer.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
		{
			buf[k++] = pathstr[i];
		}
	}
	buf[k] = 0;

	return (buf);
}

/**
 * find_path - Finds the full path of a command in the PATH string.
 * @info: Pointer to info_t struct.
 * @pathstr: PATH string.
 * @cmd: Command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	/* Check if the command starts with "./" and is executable */
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	/* Iterate through the PATH string to find the command */
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			/* Check if the constructed path is an executable command */
			if (is_cmd(info, path))
				return (path);

			if (!pathstr[i])
				break;

			curr_pos = i;
		}
		i++;
	}

	return (NULL);
}
