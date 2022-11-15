#include "shell.h"

/**
 * hsh_cd - builtin command hsh_cd, mimics cd
 * @arg_list: argumenet list given by user, generally gives which directory
 * to change to
 * @envp: environemental variable linked list to get current working direcoty
 * and also to update the variables PWD and OLDPWD
 * @bufsize: size to create our buffer for path
 * Return: 0 on success and 1 on failure
 */
int hsh_cd(char **arg_list, env_t *envp, int bufsize)
{
	char *path, *buf, *pwd;
	int l;

	buf = safe_malloc(sizeof(char) * bufsize), _memset(buf, '\0', bufsize);
	pwd = safe_malloc(sizeof(char) * bufsize), _memset(pwd, '\0', bufsize);
	getcwd(pwd, bufsize);
	path = cd_path(arg_list, envp, bufsize);
	if (path == NULL)
		return (2);
	l = chdir(path);
	if (l < 0)
	{
		/*write(0, "Error: no such file or directory\n", 33);*/
		return (2);
	}
	else
	{
		getcwd(buf, bufsize);
		update_env(envp, "OLDPWD=", pwd, bufsize);
		update_env(envp, "PWD=", buf, bufsize);
	}
	return (0);
}

/**
 * hsh_cd_help - builtin help printout for cd
 * Return: Always 0
 */
int hsh_cd_help(void)
{
	/* Maybe write more here, actualy help printout is a book */
	_write("cd usage: cd DIR\n    Change the current directory to DIR.\n");
	return (0);
}
