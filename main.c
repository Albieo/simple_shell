#include "shell.h"

/**
 * main - prints the environment
 * 
 * Return: 0 (Success)
*/
int main(int ac, char **av, char **env)
{
	char* line = NULL;
	size_t line_buf_size = 0;
	ssize_t line_size;
	(void)ac;
    	(void)av;
    	(void)env;

	while (1) 
	{
		display_prompt();

		line_size = getline(&line, &line_buf_size, stdin);
		if (line_size == -1)
			break;

		line[line_size - 1] = '\0';

		execute_command(line);
	}

	free(line);
	return (0);
}