#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

typedef int (*builtin_func)(char **);

typedef struct
{
	const char *name;
	builtin_func func;
} builtin_command;

int execute_args(char **args);
int own_cd(char **args);
int own_env(char **args);
int own_help(char **args);
int own_exit(char **args);

builtin_command builtins[] = {
    {"cd", own_cd},
    {"env", own_env},
    {"help", own_help},
    {"exit", own_exit},
};

int own_cd(char **args)
{
	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
        const char *home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		fprintf(stderr, "HOME environment variable not set\n");
		return -(1);
        }
        if (chdir(home_dir) != 0)
	{
		perror("cd");
		return (-1);
        }
	}
	else if (strcmp(args[1], "-") == 0)
	{
		const char *old_pwd = getenv("OLDPWD");
		if (old_pwd == NULL)
		{
			fprintf(stderr, "No previous directory available\n");
			return (-1);
		}
		if (chdir(old_pwd) != 0)
		{
			perror("cd");
			return (-1);
		}
		printf("%s\n", old_pwd);
	}
	else if (strcmp(args[1], "..") == 0)
	{
		if (chdir("..") != 0)
		{
			perror("cd");
			return (-1);
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
			return (-1);
		}
	}
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	if (setenv("PWD", cwd, 1) != 0)
	{
		perror("setenv");
		return (-1);
	}
	return (0);
}

int own_env(char **args)
{
	int i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (-1);
}

int own_help(char **args)
{
	printf("\n---help---\n");
	printf("This is a simple shell program.\n");
	printf("Available built-in commands:\n");
	printf("  cd\n");
	printf("  env\n");
	printf("  help\n");
	printf("  exit\n");
	printf("Use the man command for information on other programs.\n\n");
	return (-1);
}

int own_exit(char **args)
{
	if (args[1])
	{
		exit(atoi(args[1]));
	}
	else
	{
		exit(0);
	}
}

int execute_args(char **args)
{
	if (args[0] == NULL)
	{
		return (-1);
	}
	for (size_t i = 0; i < sizeof(builtins) / sizeof(builtin_command); i++) {
		if (strcmp(args[0], builtins[i].name) == 0)
		{
			return (builtins[i].func(args));
		}
	}
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		fprintf(stderr, "Fork failed\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (status);
	}
}
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	characters = getline(&line, &bufsize, stdin);
	if (characters == -1)
	{
		if (feof(stdin))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(line);
			perror("Error while reading the line from stdin");
			exit(EXIT_FAILURE);
		}
	}
	if (line[characters - 1] == '\n')
	{
		line[characters - 1] = '\0';
	}
	return (line);
}

char **split_line(char *line)
{
	char **args = NULL;
	size_t n = 0;
	args = malloc(sizeof(char *) * n);
	if (args == NULL)
	{
		return (NULL);
	}
	n = 0;
	char *token = strtok(line, " ");
	while (token != NULL)
	{
		args[n] = token;
		token = strtok(NULL, " ");
		n++;
	}
	args[n] = NULL;
	return (args);
}

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("^C\n");
		exit(EXIT_SUCCESS);
	}
}
int main(__attribute__((unused)) int argc, char **argv)
{
	signal(SIGINT, signal_handler);
	int interactive = isatty(STDIN_FILENO);
	char *line;
	char **args;
	int status = -1;

	while (1)
	{
		if (interactive)
		{
			printf("simple_shell $ ");
			fflush(stdout);
			line = read_line();
		}
		else
		{
			line = read_line();
		}
		args = split_line(line);
		status = execute_args(args);

		free(line);
		free(args);
	}
	return (0);
}
