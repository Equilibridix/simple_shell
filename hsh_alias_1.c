#include "shell.h"

/**
 * hsh_alias - builtin for alias function
 * @argv: argument vector
 * @env_p: env list
 * @mode: Execution mode for the program, 0 or !0
 * Description: Complicated parent function for 
 * the alias functionality of hsh. 
 * Uses two modes to allow it being called from
 * multiple points from within our program.
 * Return: 0 on success, 2 on failure.
 */

int hsh_alias(char **argv, env_t *env_p, int mode)
{
	static alias list = {NULL, NULL, NULL};
	int ret;
	(void) env_p;

	if (mode == 0)
	{
		argv[0] = hsh_alias_search(&list, argv[0]);
		return (0);
	}
	else
	{
		if (argv[1] == NULL)
			ret = hsh_alias_printall(&list);
		else if (argv[2] != NULL)
		{
			_write("Error. Too many arguments.");
			return (2);
		}
		else
		{
			ret = hsh_alias_print(&list, argv);
			if (ret == 1)
				ret = hsh_alias_add(&list, argv);
		}
	}
	return (ret);
}

/**
 * hsh_alias_search - find alias values matching their key
 * @list: alias linked list
 * @arg: alias to search for
 *
 * Return: matching alias value, or NULL
 */

char *hsh_alias_search(alias *list, char *arg)
{
	while (list != NULL && list->key != NULL)
	{
		if (_str_match_strict(arg, list->key))
			return (list->val);
		list = list->next;
	}
	return (NULL);
}

/**
 * hsh_alias_printall - printout the full alias list
 * @list: alias linked list
 *
 * Return: Always 0
 */
int hsh_alias_printall(alias *list)
{
	while (list != NULL && list->key != NULL)
	{
		_write("alias ");
		_write(list->key);
		_write("='");
		_write(list->val);
		_write("'\n");
		list = list->next;
	}
	return (0);
}

/**
 * hsh_alias_print - print out an alias if match found
 * @list: alias linked list
 * @argv: argument vector
 *
 * Return: 1 if no match needed, 2 on alias not found, 0 on success
 */
int hsh_alias_print(alias *list, char **argv)
{
	char *val;

	val = _strstr(argv[1], "=");
	if (val != NULL)
		return (1);

	val = hsh_alias_search(list, argv[1]);
	if (val == NULL)
	{
		_write("alias not found\n");
		return (2);
	}
	else
	{
		_write("alias ");
		_write(argv[1]);
		_write("='");
		_write(val);
		_write("'\n");
	}
	return (0);
}

/**
 * hsh_alias_add - add, edit, or print alias in the list
 * @list: alias linked list
 * @argv: argument vector
 *
 * Return: Always 0;
 */
int hsh_alias_add(alias *list, char **argv)
{
	alias *newnode;
	char *key, *val;
	int i, j;

	val = _strstr(argv[1], "=");
	if (val != NULL)
		val += 1;

	val = _strdup(val);

	for (i = 0; argv[1][i] != '='; i++)
		;
	key = safe_malloc(sizeof(char) * (i + 1));
	for (j = 0; j < i; j++)
		key[j] = argv[1][j];
	key[j] = '\0';

	while (list->next != NULL && !_str_match_strict(key, list->key))
		list = list->next;
	if (list->key == NULL || _str_match_strict(key, list->key))
	{
		list->key = key;
		list->val = val;
	}
	else if (list->next == NULL)
	{
		newnode = safe_malloc(sizeof(alias));
		newnode->key = key;
		newnode->val = val;
		newnode->next = NULL;
		list->next = newnode;
	}
	else
		list->val = val;
	return (0);
}
