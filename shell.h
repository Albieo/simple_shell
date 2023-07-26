#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* for read/write buffers */
#define BUF_SIZE 1024
#define BUF_FLUSH -1

#define PROMPT "$ "

/**
 * struct info - parameters and return value
 * @cmd_buf: the buffer for cmd
 * @argv: argument vectors
 * @lineptr: pointer to the line
 * @linecount: line count
 * @status: status struct
 */
typedef struct info
{
	char cmd_buf[BUF_SIZE];
	char *argv[2];
	char *lineptr;
	size_t linecount;
	int status;
} info_t;

/* shell.c */
void hsh_loop(void);

/* string.c */
int _strlen(char *s);
void _puts(char *str);
int _putchar(char c);

#endif /* SHELL_H */