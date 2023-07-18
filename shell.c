#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_COMMAND_LENGTH 1024

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	ssize_t num_chars_read;
	pid_t pid;
	int status;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 13);

		num_chars_read = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);
		if (num_chars_read == -1)
			break;

		command[num_chars_read - 1] = '\0';

		pid = fork();

		if (pid < 0)
			break;

		else if (pid == 0)
		{
			char **argv = (char **)malloc(2 * sizeof(char *));
			argv[0] = command;
			argv[1] = NULL;
			execve(command, argv, NULL);

			free(argv);
			_exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}

	return (0);
}
