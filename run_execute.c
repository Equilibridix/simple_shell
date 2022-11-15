#include "shell.h"

/**
 * run_execute - an execution function for the command given
 * @arg_list: argument list of what is inputed by user
 * @env_p: the linked list containing environmental variables
 * @cmd_size: size that command should be allocated for
 * Description: Checks if the command given is given the path (i.e /bin/ls)
 * if not, then the function will find the path for the command and if it fails
 * to find the command, an Error: command not found will be printed.
 * Return: status if success or 127 if failure.
 */
int run_execute(char **arg_list, env_t *env_p, int cmd_size)
{
	char *command, *path;
	char **search_path;
	int stat, num, m;

	search_path = NULL;
	num = 0;
	command = safe_malloc(sizeof(char) * cmd_size);
	path = safe_malloc(sizeof(char) * cmd_size);
	_strcpy(command, arg_list[0]);
	if (_strchr(command, '/') != NULL)
		stat = execute_func(command, arg_list, env_p);
	else
	{
		m = get_path(path, env_p);
		if (m != 0)
		{
			_write("Error: Cannot find PATH variable\num");
			return (127);
		}
		search_path = tokenize_path(search_path, path, cmd_size);
		num = create_path(command, search_path);
		if (num == 0)
			stat = execute_func(command, arg_list, env_p);
	}
	if (num == 0)
		return (stat);
	else
		return (127);
}

/**
 * execute_func - function that runs the execve system call.
 * @command: full path to the command
 * @args: the arguement list (if any) given by the user.
 * @envp: environemental variable list
 * Return: 0 on success and 2 on failure
 */
int execute_func(char *command, char **args, env_t *envp)
{
	pid_t mypid;
	int stat, i;
	char **array;


	mypid = fork();
	if (mypid == 0)
	{
		array = list_to_array(envp);
		i = execve(command, args, array);
		if (i < 0)
		{
			_write("Error: command not found\num");
			return (2);
			_exit(1);
		}
	}
	else
	{

		mypid = wait(&stat);
		if (WIFEXITED(stat))
			return (stat);
	}
	return (2);
}
