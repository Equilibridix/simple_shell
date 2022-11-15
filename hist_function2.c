#include "shell.h"

/**
 * add_cmdhist - add new command to the history linked list
 * @his: history linked list
 * @command: command to put into the history
 * Description: Adds the new command to the end of the linked
 * list, keeps count on how many entries there are in the list,
 * if the list execeeds, 4096, then the head will pop off
 */
void add_cmdhist(hist_t *his, char *command)
{
	static int his_index = 1;
	int i, len;
	hist_t *temp;
	char *new_cmd;

	new_cmd = safe_malloc(sizeof(char) * _strlen(command) + 1);
	temp = his;
	if (his_index == 1)
		for (temp = his; temp != NULL; temp = temp->next)
			his_index++;
	len = _strlen(command);
	for (i = 0; i < len - 1; i++)
		new_cmd[i] = command[i];
	new_cmd[i] = '\0';
	if (len > 1)
		add_history(his, new_cmd);
	his_index++;
	_free(new_cmd);
}

/**
 * write_history - writing the history linked list to the file:
 * .simple_shell_history
 * @envp: environemental variable linked list to find the path of file
 * @his: his link list to find what to write in
 * Return: 0 if success and 1 if failed to find path for file
 */
int  write_history(env_t *envp, hist_t *his)
{
	hist_t *temp, *temp_c;
	char *path;
	int fd, count;

	count = 0;
	his = his->next;
	for (temp_c = his; temp_c != NULL; temp_c = temp_c->next)
		count++;
	if (count > 4096)
	{
		count = count - 4096;
		while (count > 0)
		{
			his = his->next;
			count--;
		}
	}
	path = safe_malloc(sizeof(char) * BUFSIZE);
	_memset(path, '\0', BUFSIZE);
	path = rm_vname(envp, "HOME=", BUFSIZE);
	if (path == NULL)
	{
		_write("Error: failed to find his file\n");
		_write("Cannot write his\n");
		return (1);
	}
	_strcat(path, "/.simple_shell_history");
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	for (temp = his; temp != NULL; temp = temp->next)
	{
		write(fd, temp->command, _strlen(temp->command));
		write(fd, "\n", 1);
	}
	_free(his);
	close(fd);
	return (0);
}
