#ifndef SHELL_H
#define SHELL_H

#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\0'
#define MAX_ARGS 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

void display_prompt();
void execute_command(char* command);
void builtin_exit(void);

#endif /* SHELL_H */