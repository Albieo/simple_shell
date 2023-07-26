#include "shell.h"

/**
 * hsh_loop - main shell loop
 */
void hsh_loop(void)
{
	ssize_t r;
	info_t info = {0};
	pid_t child_pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			_puts(PROMPT);

		r = read(STDIN_FILENO, info.cmd_buf, BUF_SIZE);
		if (r == -1)
		{
			perror("read");
			continue;
		}
		else if (r == 0)
		{
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			break;
		}

		info.cmd_buf[r] = '\0';
		if (info.cmd_buf[r - 1] == '\n')
			info.cmd_buf[r - 1] = '\0';

		if (access(info.cmd_buf, X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
			{
				perror("fork");
			}
			else if (child_pid == 0)
			{
				execl(info.cmd_buf, info.cmd_buf, NULL);
				perror("execl");
				_exit(EXIT_FAILURE);
			}
			else
			{
				wait(&info.status);
			}
		}
		else
		{
			perror("Command not found");
		}
	}
}


/**
 * main - main program
 * 
 * Return: EXIT_SUCCESS
*/
int main(void)
{
	hsh_loop();
	return (EXIT_SUCCESS);
}