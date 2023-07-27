#include "shell.h"

/**
 * display_prompt - shows the prompt in terminal
*/
void display_prompt(void)
{
	char *prompt = "$ ";
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, prompt, 2);
		fflush(stdout);
	}
}

/**
 * execute_command - xecuting the specified command in the shell.
*/
void execute_command(char* command)
{
	char* args[MAX_ARGS];
	int arg_index = 0;
	pid_t pid;
	int status;
	char* token = strtok(command, " \t");

	while (token != NULL && arg_index < MAX_ARGS - 1)
	{
		args[arg_index++] = token;
		token = strtok(NULL, " \t");
	}
	args[arg_index] = NULL;

	if (arg_index == 0)
	{
		return;
	}

	if (_strcmp(args[0], "exit") == 0)
	{
		builtin_exit();
		return;
	}

	pid = fork();

	if (pid < 0)
	{
		_puts("Fork error");
		_putchar('\n');
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execvp(args[0], args);
		_puts("Execve error");
		_putchar('\n');
		_exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
