#include "simple_shell.h"

/**
 * handle_fork - handle the fork process
 * @args: array of a command and arguments
 * @argo: path to command we want to exec
 */
void handle_fork(char *args[])
{
	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(args[0], args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * execute - Execute a command given as an array of arguments.
 * @args: the array
 * if the command is a builtin, it is executed directly.
 * if the command has a path prefix, it is executed directly.
 * Otherwise, the directories in PATH are searched for the command
 * and it is executed if found.
 */
void execute(char *args[])
{
	char *path, *path_copy, *dir;
	struct dirent *entry;

	if (is_builtin(args[0]))
	{
		run_builtin(args);
		return;
	}
	else if (has_path_prefix(args[0]))
	{
		handle_fork(args);
		return;
	}
	path = getenv("PATH");
	path_copy = _strdup(path);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		DIR *dp = opendir(dir);

		if (dp == NULL)
		{
			perror("opendir");
			exit(EXIT_FAILURE);
		}
		while ((entry = readdir(dp)) != NULL)
		{
			char cmd_path[1024];

			if (_strcmp(entry->d_name, args[0]) == 0)
			{
				_strcpy(cmd_path, dir);
				_strcat(cmd_path, "/");
				_strcat(cmd_path, entry->d_name);
				if (access(cmd_path, X_OK) == -1)
				{
					write(STDOUT_FILENO, "Command not found: ", 19);
					write(STDOUT_FILENO, args[0], strlen(args[0]));
					write(STDOUT_FILENO, "\n", 1);
					closedir(dp);
					free(path_copy);
					return;
				}
				args[0] = cmd_path;
				handle_fork(args);
				closedir(dp);
				free(path_copy);
				return;
			}
		}
		closedir(dp);
		dir = strtok(NULL, ":");
	}
	perror("Command not found");
	free(path_copy);
	return;
}

/**
 * is_builtin - check if the given command is a builtin
 * @cmd: command to check
 * Return: 1 if yes or 0 if no
 */
int is_builtin(char *cmd)
{
	return (_strcmp(cmd, "cd") == 0 ||
		       _strcmp(cmd, "exit") == 0 || _strcmp(cmd, "env") == 0);
}

/**
 * run_builtin - Runs a builtin command
 * @args: array of builtin command arg[0] and its arguments
 */
void run_builtin(char **args)
{
	if (_strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			write(STDOUT_FILENO, "cd: expected argument to \"cd\"\n", 31);
		}
		else
		{
			if (chdir(args[1]) != 0)
			{
				perror("chdir");
			}
		}
	}
	else if (_strcmp(args[0], "exit") == 0)
	{
		exit_shell(args);
	}
	else if (_strcmp(args[0], "env") == 0)
	{
		shell_env(args);
	}
}

/**
 * has_path_prefix - Checks if the given command has a path prefix.
 * @cmd: the command
 * Return: 1 on find, 0 on not found
 */
int has_path_prefix(char *cmd)
{
	return (_strchr(cmd, '/') != NULL);
}
