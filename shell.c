#include "simple_shell.h"

/**
 *check_interactive - execute cmd in interactive mode
 *Return: void
 */
int check_interactive(void)
{
	return (isatty(STDIN_FILENO));
}

/**
 * main - entry point
 * Return: 0 on success
 */
int main(void)
{
	int flag_isatty = isatty(STDIN_FILENO);
	char *line = NULL, **args;
	size_t buff;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		args = NULL;
		buff = 0;

		if (flag_isatty)
			write(STDOUT_FILENO, "simple_shell $ ", 15);
		if (getline(&line, &buff, stdin) == -1)
		{
			if (flag_isatty)
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(EXIT_SUCCESS);
		}
		if (line[_strlen(line) - 1] == '\n')
			line[_strlen(line) - 1] = '\0';
		args = tokenize(line);
		if (args != NULL && args[0] != NULL)
		{
			execute(args);
		}
		free(args);
	}
	return (0);
}
