#include "shell.h"

/**
 * _getline - Read input and put in buffer
 * @b: buffer structure
 * @fd: file descriptor to read from
 * @envp: enviornment structure
 * Return: Always 0. Exit on failure or EOF
 */
int _getline(buffer *b, int fd, env_t *envp)
{
	int offset, num;

	offset = 0, num = 0;
	while ((num = read(fd, b->buf + offset, b->size - offset)) > 0 &&
			b->buf[b->bp + offset + num - 1] != '\n')
	{
		buff_reallocate(b);
		offset += num;
	}
	if (num == 0)
	{
		if (fd > 2)
			close(fd);
		history_wrapper("", envp, 'w');
		defer_free(FREE_ADDRESSES);
		_exit(0);
	}
	b->buf[num + offset] = '\0';
	return (0);
}

/**
 * _getline_fileread - wrapper function that reads a file into buffer
 * @b: buffer structure
 * @envp: enviornment structure
 *
 * Return: 1 on file not exist, else 0
 */
int _getline_fileread(buffer *b, env_t *envp)
{
	int fd, i;
	char *filename, *f_filename;

	/* scan through buffer and pull out filename to read */
	i = b->bp;
	while (_is_whitespace(b->buf[i]))
		i++;
	if (!_str_match_tonull(b->buf + i, "simple_shell") || b->buf[i] == '\0')
		return (0);
	while (!_is_whitespace(b->buf[i]) && b->buf[i] != '\0')
		i++;
	while (_is_whitespace(b->buf[i]) && b->buf[i] != '\0')
		i++;
	if (b->buf[i] == '\0')
		fd = -1;
	else
	{
		filename = b->buf + i;
		while (!_is_whitespace(b->buf[i]) && b->buf[i] != '\0')
			i++;
		b->buf[i] = '\0';
		make_path(&f_filename, filename, "PWD", envp);
		fd = open(f_filename, O_RDONLY);
	}
	if (fd == -1)
	{
		history_wrapper("", envp, 'w');
		defer_free(FREE_ADDRESSES);
		_exit(1);
	}
	_getline(b, fd, envp);
	close(fd);
	return (0);
}
