#include "shell.h"

/**
 * print_cmdline - prints the command line or PS1
 */
void print_cmdline(void)
{
	char *str;

	str = "(^.^) ";
	write(0, str, 6);
}

/**
 * safe_malloc - allocates memory and handles errors
 * @size: size of space to allocate
 *
 * Return: pointer to new space
 */
void *safe_malloc(size_t size)
{
	void *temp;

	temp = malloc(size);
	if (temp == NULL)
	{
		_write("Out of Memory, Exiting (._.)\n");
		defer_free(FREE_ADDRESSES);
		_exit(4);
	}
	defer_free(temp);
	return (temp);
}

/**
 * _write_err - Write to standard error
 * @s: string to write to stderr
 */
void _write_err(char *s)
{
	write(STDERR_FILENO, s, _strlen(s));
}

/**
 * rm_vname - removes varaiable name of an environemental variable
 * @envp: the environemental varaible name and value string
 * @name: the variable name to search for
 * @bufsize: the size of the path
 * Return: a string containing the path
 */
char *rm_vname(env_t *envp, char *name, int bufsize)
{
	char *pwd;
	env_t *temp;

	pwd = safe_malloc(sizeof(char) * bufsize);
	_memset(pwd, '\0', bufsize);
	temp = envp;
	for (; ; temp = temp->next)
	{
		if (_str_match(temp->val, name))
		{
			_strcpy(pwd, temp->val);
			break;
		}
		else if (temp->next == NULL)
		{
			_free(pwd);
			return (NULL);
		}
	}
	while (*pwd != '=')
		pwd++;
	pwd++;
	return (pwd);
}

/**
 * get_env_value - get a the value from an env variable
 * @envp: the env list
 * @name: key/name of the env variable
 * Return: a pointer to the value, NULL if none found
 */
char *get_env_value(env_t *envp, char *name)
{
	char *val;

	while (1)
	{
		if (_str_match(envp->val, name))
		{
			val = envp->val;
			break;
		}
		else if (envp->next == NULL)
			return (NULL);
		envp = envp->next;
	}
	while (*val++ != '=')
		;
	return (val);
}
