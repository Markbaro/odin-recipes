#include "simple_shell.h"

/**
 * print_str-prints string to SSTDOUT
 * @string : input string
 * Return: void
*/
void print_str(char *string)
{
	write(STDOUT_FILENO, string, strlen(string));
}
