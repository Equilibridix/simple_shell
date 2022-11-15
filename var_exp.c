#include "shell.h"

/**
 * variable_expansion - Expand variables in the buffer.
 * @b: buffer structure.
 * @envp: Enviorn structure.
 * @return_val: return value of previous command
 * Description: Expands variables from input of $VALUE.
 *				$? = Last return value.
 *				$$ = Process ID.
 *				$VALUE = Any enviormental variable. Deletes if found none.
 */

void variable_expansion(buffer *b, env_t *envp, int return_val)
{
	char *hold;
	int index, offset;


	offset = index = 0;
	while ((index = _strstr_int(b->buf + b->bp + offset, "$")) >= 0 &&
		index < _strpbrk_int(b->buf + b->bp + offset, "\n;&|"))
	{
		index += offset;
		offset = index + 1;
		if (b->buf[b->bp + index + 1] == '?')
		{
			hold = _itoa(return_val, 1);
			buff_word_erase(b, b->bp + index);
			buff_insert(b, hold, b->bp + index);
			_free(hold);
		}
		else if (b->buf[b->bp + index + 1] == '$')
		{
			buff_word_erase(b, b->bp + index);
			hold =  _getpid();
			buff_insert(b, hold, b->bp + index);
		}
		else if (!_is_whitespace(b->buf[b->bp + index + 1]))
		{
			hold = rm_vname(envp, b->buf + b->bp + index + 1, b->size);
			buff_word_erase(b, b->bp + index);
			if (hold != NULL)
				buff_insert(b, hold, b->bp + index);
		}
	}
}

/**
 * _getpid - gets the mypid of the current process
 * Return: a string of the mypid
 */
char *_getpid(void)
{
	char path[BUFSIZE], id[BUFSIZE];
	char *hold, *ppid;
	pid_t mypid;
	int fd;

	path[0] = id[0] = '\0';
	mypid = fork();
	if (mypid == 0)
	{
		defer_free(FREE_ADDRESSES);
		_exit(0);
	}
	else
	{
		hold = _itoa(mypid, 1);
		_strcat(path, "/proc/");
		_strcat(path, hold);
		_strcat(path, "/stat");
		fd = open(path, O_RDONLY);
		if (fd > 0)
		{
			read(fd, id, 100);
			ppid = _getTok(id, 4);
		}
		wait(NULL);
	}
	return (ppid);
}

/**
 * _getTok - gets the nth element of buffer, seperated by space
 * @num: which element to get
 * @stat: stat array
 * Return: an array the nth element or null if failed
 */
char *_getTok(char *stat, int num)
{
	int i, j, space_count;
	char *buf;

	buf = safe_malloc(sizeof(char) * BUFSIZE);
	space_count = 0;
	for (i = 0, j = 0; stat[i] != '\0' || space_count <= num; i++)
	{
		if (stat[i] == ' ' && space_count == num - 1)
		{
			buf[j] = '\0';
			return (buf);
		}

		if (stat[i] == ' ' && space_count != num - 1)
			space_count++;
		else if (stat[i] != ' ' && space_count == num - 1)
			buf[j++] = stat[i];
	}
	return (NULL);
}
