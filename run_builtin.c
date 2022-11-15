#include "shell.h"

/**
 * run_builtin - checking arg_list for builtins and executing found cmd.
 * @arg_list: argument list.
 * @env_p: enviorn list.
 * @bufsize: buffer size.
 * Return: 0 on found builtin, 1 on found nothing, 2 on builtin error.
 */

int run_builtin(char **arg_list, env_t *env_p, int bufsize)
{
	int i, size, stat;
	builtin table[] = {
	{"exit", hsh_exit},     {"env", hsh_env},
	{"setenv", hsh_setenv}, {"unsetenv", hsh_unsetenv},
	{"cd", hsh_cd},         {"history", hsh_history},
	{"help", hsh_help},     {"alias", hsh_alias}
	};

	size = ARRAY_SIZE(table);
	for (i = 0; i < size; i++)
	{
		if (_str_match_strict(arg_list[0], table[i].name))
		{
			stat = table[i].func(arg_list, env_p, bufsize);
			return (stat);
		}
	}
	return (1);
}
