#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1000
extern char **environ;

extern char **environ;
void handle_fork(char *args[]);
void execute(char *args[]);
int is_builtin(char *cmd);
void run_builtin(char **args);
int has_path_prefix(char *cmd);
void exit_shell(char **args);
void shell_env(__attribute__((unused)) char **args);
char **tokenize(char *input_str);
/*void print_str(char *string);*/
void print_str(const char *format, ...);
size_t _strlen(const char *str);
int _strcmp(const char *str1, const char *str2);
char *_strdup(const char *str);
char *_strchr(const char *str, int ch);
char *_strcpy(char *dest, const char *src);
char *_strcat(const char *str1, const char *str2);
#endif
