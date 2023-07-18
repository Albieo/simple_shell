#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_COMMAND_LENGTH 1024

int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		write(STDOUT_FILENO, "SimpleShell> ", 13);

		ssize_t num_chars_read = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);
		pid_t pid = fork();

		if (num_chars_read == -1)
        	break;

		command[num_chars_read - 1] = '\0';

		if (pid < 0)
			break;

		else if (pid == 0)
		{
    		char *argv[] = {command, NULL};
			execve(command, argv, NULL);

			_exit(EXIT_FAILURE);
		}
		else
		{
			int status;
			waitpid(pid, &status, 0);
		}
	}

	return (0);
}
