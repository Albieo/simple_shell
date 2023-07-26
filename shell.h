#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>
#include <errno.h>

#define BUF_SIZE 1024
#define PROMPT "$ "

bool check_file_status(char *pathname);
void _execute(char *arguments, char **envp);
char **split_string(char *str, const char *delimiter);
void free_string_array(char **arr);
int _putchar(char c);
int _puts(char *str);

#endif /* SHELL_H */
