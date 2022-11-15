#include "shell.h"

/**
 * _write - Write information to STDOUT
 * @s: string;
 */

void _write(char *s)
{
	write(STDOUT_FILENO, s, _strlen(s));
}

/**
 * update_path - rewrites PWD path to not include sybols
 * @arg_list: arguement list given by the user to determine directory
 * @envp: environemental variable linked list
 * @path: current path to be updated
 * @bufsize: the size of the current path
 * Return: a path without any symbols such as (., .., ~, or -)
 */

char *update_path(char **arg_list, env_t *envp, char *path, int bufsize)
{
	int i, slashcount, flag;
	char *dir, *newpath;

	newpath = safe_malloc(sizeof(char) * bufsize);
	_memset(newpath, '\0', bufsize);
	_strcpy(newpath, path);
	for (i = 0, slashcount = 0; newpath[i] != '\0'; i++)
	{
		if (newpath[i] == '/')
			slashcount++;
	}
	dir = arg_list[1];
	if (_strcmp(dir, ".") == 0)
		newpath = rm_vname(envp, "PWD=", bufsize);
	else if (_strcmp(dir, "..") == 0)
	{
		/* check for if things behind it + append*/
		for (flag = 0, i = 0; flag < slashcount - 1; i++)
		{
			if (newpath[i] == '/')
				flag++;
		}
		newpath[i - 1] = '\0';
	}
	else if (_strcmp(dir, "~") == 0)
		newpath = rm_vname(envp, "HOME=", bufsize);
	else if (_strcmp(dir, "-") == 0)
		newpath = rm_vname(envp, "OLDPWD=", bufsize);
	return (newpath);

}

/**
 * list_to_array - converts a linked list to an array
 * @envp: environemental list to convert
 * Return: a 2D array containing strings contained in linked list
 */

char **list_to_array(env_t *envp)
{
	char **array;
	env_t *temp;
	int count, i, len;

	for (temp = envp, count = 0; temp != NULL; temp = temp->next)
		count++;
	array = malloc(sizeof(char *) * (count + 1));
	for (temp = envp, i = 0; temp != NULL; temp = temp->next, i++)
	{
		len = _strlen(temp->val);
		array[i] = safe_malloc(sizeof(char) * (len + 1));
		_memset(array[i], '\0', (len + 1));
		_memcpy(array[i], temp->val, len);
	}
	array[i] = NULL;
	return (array);
}

/**
 * _strcmp - compares two strings
 * @s1: string one to compare
 * @s2: string two to compare
 * Return: an integer less than 0 if s1 is found
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] >  s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

/**
 * _strcpy - copies string pointed by src to the buffer point to by dest
 * @dest: destination where i want
 * @src: string that i want to copy
 * Return: the point to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != 0; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}
