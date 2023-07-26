#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_COMMAND_LENGTH 1024

/**
 * main - shell program
 *
 * Return: 0 (Success)
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *args[MAX_COMMAND_LENGTH / 2];
	ssize_t num_chars_read;
	int status;
	int arg_count;
	pid_t pid;

	while (1)
	{
		write(1, ":) ", 3);
		fflush(stdout);
		num_chars_read = read(0, command, MAX_COMMAND_LENGTH);

		if (num_chars_read == -1)
		{
			perror("Error reading input");
			break;
		}

		if (num_chars_read == 0)
		{
			write(1, "\n", 1);
			break;
		}

		command[num_chars_read - 1] = '\0';

		arg_count = 0;
		args[arg_count] = strtok(command, " ");
		while (args[arg_count] != NULL && arg_count < MAX_COMMAND_LENGTH / 2)
		{
			arg_count++;
			args[arg_count] = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		if (strcmp(args[0], "exit") == 0)
		{
            		break;
		}

		pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
			break;
		}
		else if (pid == 0)
		{
			execvp(args[0], args);
			perror("Command execution failed");
			_exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}

	return (0);
}
