#include "simple_shell.h"

/**
 * tokenize - tokenizes input string
 * @input_str: input string to parse
 * Return: Pointer to the new array
 */
char **tokenize(char *input_str)
{
	char **args = NULL, *token;
	int n = 0, i;

	args = malloc(sizeof(char *) * n + 1);

	if (args == NULL)
	{
		return (NULL);
	}

	i = 0;
	token = strtok(input_str, " ");

	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	return (args);
}
