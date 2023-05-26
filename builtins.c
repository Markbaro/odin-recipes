#include "simple_shell.h"
/**
  * exit_shell - exits the shell
  * @args : array of exit codes
  * Return: 0 on success
  */
void exit_shell(char **args)
{
	if (args[1])
	{
		int status = atoi(args[1]);

		free(args);
		exit(status);
	}
	else
	{
		free(args);
		exit(0);
	}
}
/**
 * shell_env - function that prints enviroment variables
 * @args: arguments
 * Return: system enviroment variables
 */
void shell_env(char **args)
{
	int i = 0;
	size_t len;
	(void)args;

	while (environ[i])
	{
		len = strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
