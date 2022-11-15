#include "shell.h"

/**
 * get_path - copies the $PATH into the string path
 * @path: string to copy the $PATH into
 * @list: environemental variable list
 * Return: 0 if successly found PATH variable and 1 if PATH
 * not found
 */

int get_path(char *path, env_t *list)
{
	env_t *temp;

	temp = list;
	for (; temp->next != NULL; temp = temp->next)
	{
		if (_str_match_tonull(temp->val, "PATH=") != 0)
		{
			_strcpy(path, temp->val);
			return (0);
		}
	}
	return (1);
}

/**
 * tokenize_path - creates an array of strings, each string is a directory
 * in the $PATH variable
 * @search_path: array of strings that contains a searchable path for each
 * string space.
 * @path: the string containing $PATH
 * @size: size of buffer
 * Description: This also mallocs search_path with how many directories are
 * found in path.
 * Return: a 2D array of tokens
 */
char **tokenize_path(char **search_path, char *path, int size)
{
	int i, count, s_index;
	char *temp, *buf;

	buf = safe_malloc(sizeof(char) * size);
	buf[0] = '\0';
	for (i = 0, count = 1; path[i] != '\0'; i++)
	{
		if (path[i] == ':')
			count++;
	}
	count++;
	search_path = safe_malloc(sizeof(char *) * count);
	/* skip the PATH= */
	for (temp = path; *temp != '='; temp++)
		;
	temp++, s_index = 0;
	do {
		if (*temp == ':' || *temp == '\0')
		{
			_strncat(buf, "/", 1);
			search_path[s_index] = safe_malloc(sizeof(char) * size);
			search_path[s_index][0] = '\0';
			_strncat(search_path[s_index], buf, _strlen(buf));
			s_index++;
			buf[0] = '\0';
		}
		else
			_strncat(buf, temp, 1);
	} while (*temp++);
	search_path[s_index] = safe_malloc(sizeof(char *));
	search_path[s_index] = NULL;
	return (search_path);
}

/**
 * create_path - checks whether or not the command exist or not
 * @command: command given by user, need to append to end of path strings
 * @search_path: array of path strings to check for existance of command
 * Description: Checks whether or not a command exist by trying to open it
 * in the different path directories.
 * Return: 0 if found and -1 if not;
 */
int create_path(char *command, char **search_path)
{
	int i, fd;

	for (i = 0; search_path[i] != NULL; i++)
	{
		_strncat(search_path[i], command, _strlen(command));
		fd = open(search_path[i], O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			_strcpy(command, search_path[i]);
			return (0);
		}
	}
	write(0, "Error: command not found\n", 25);
	return (-1);
}
