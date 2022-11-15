#include "shell.h"

/**
 * alias_expansion - wrapper function for checking and replacing aliases
 * @b: buffer structure
 * @env_p: enviornment struct to pass along
 * Return: 1 on alias replacement, 0 if no replacement
 */
int alias_expansion(buffer *b, env_t *env_p)
{
	static int stop = 2;
	int i, size;
	char *arg, *arg_copy;

	size = 0, i = 0;
	while (b->buf[b->bp] == ' ' || b->buf[b->bp] == '\t')
		b->bp++;
	while (!_is_whitespace(b->buf[b->bp + size]))
		size++;

	arg = safe_malloc(sizeof(char) * (size + 1));
	arg_copy = arg;

	while (i < size)
		arg[i] = b->buf[b->bp + i], i++;
	arg[i] = '\0';

	hsh_alias(&arg, env_p, 0);

	if (arg != NULL)
	{
		buff_word_erase(b, b->bp);
		buff_insert(b, arg, b->bp);
		_free(arg_copy);
		if (stop++ == 10)
		{
			stop = 0;
			return (0);
		}
		return (1);
	}
	else
		_free(arg);
	stop = 0;
	return (0);
}
