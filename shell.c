#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - writes the string to stdout
 * @str: The string to print
 *
 * Return: index of string.
 */
int _puts(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
	return (i);
}

/**
 * main - shell program
 *
 * Return: 0 (Success)
*/
int main(void)
{
	char *buff = NULL;
	size_t buff_size = 0;
	ssize_t bytes;
	bool _pipe = false;

	while (1 && !_pipe)
	{
		if (isatty(STDIN_FILENO) == 0)
			_pipe = true;

		_puts(PROMPT);

		bytes = getline(&buff, &buff_size, stdin);
		if (bytes == -1)
		{
			_putchar('\n');
			perror("Error (getline)");
			free(buff);
			exit(EXIT_FAILURE);
		}

		if (buff[bytes - 1] == '\n')
			buff[bytes - 1] = '\0';

		_execute(buff, NULL);
	}

	free(buff);
	return (0);
}

/**
 * _execute - function for executing the specified
 * command (arguments) in the shell
 *
 * @arguments: A pointer to a character array (C-string) that
 * holds the command to be executed.
 * @envp: A pointer to a null-terminated array of
 * character pointers reps to execute
*/
void _execute(char *arguments, char **envp)
{
	pid_t wpid;
	char **argv;

	if (!check_file_status(arguments))
	{
		_puts("./shell: ");
		perror(NULL);
		return;
	}

	wpid = fork();
	if (wpid == -1)
	{
		perror("Error (fork)");
		exit(EXIT_FAILURE);
	}

	if (wpid == 0)
	{
		if (arguments[strlen(arguments) - 1] == '\n')
			arguments[strlen(arguments) - 1] = '\0';

		argv = split_string(arguments, " ");
		execve(argv[0], argv, envp);
		perror("Error (execve)");
		free_string_array(argv);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}

	exit(0);
}

/**
 * check_file_status - checks if the given file or command is executable.
 * @pathname: string representing the path to a file or a command name.
 *
 * Return: true (Success), false (Otherwise)
*/
bool check_file_status(char *pathname)
{
	return access(pathname, X_OK) == 0;
}

/**
 * split_string - It tokenizes the input string str into individual
 * substrings 
 * @str: pointer to the input string that needs to be split.
 * @delimiter: pointer to a constant string (character array)
 * that specifies the delimiter used to split the input string.
 *
 * Return: pointer to a dynamically allocated array of strings
*/
char **split_string(char *str, const char *delimiter)
{
	char **tokens = NULL;
	char *token;
	int size = 0;

	token = strtok(str, delimiter);

	while (token != NULL)
	{
		tokens = realloc(tokens, sizeof(char *) * (size + 1));
		if (!tokens)
		{
			_putchar('\n');
			perror("Error (realloc)");
			exit(EXIT_FAILURE);
		}

		tokens[size++] = strdup(token);
		token = strtok(NULL, delimiter);
	}

	tokens = realloc(tokens, sizeof(char *) * (size + 1));
	if (!tokens)
	{
		perror("Error (realloc)");
		exit(EXIT_FAILURE);
	}
	tokens[size] = NULL;

	return (tokens);
}

/**
 * free_string_array - function is responsible for freeing
 * the memory allocated for an array of strings
 * @arr: A pointer to an array of strings
*/
void free_string_array(char **arr)
{
	int i;

	if (arr == NULL)
		return;

	for (i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
	}

	free(arr);
}
