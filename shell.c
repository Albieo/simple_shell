#include "shell.h"

void display_prompt()
{
    if (isatty(STDIN_FILENO))
    {
        char prompt[] = "$ ";
        _puts(prompt);
        fflush(stdout);
    }
}

void execute_command(char* command)
{
    char* trimmed_command = strtok(command, " \t");
    pid_t pid;
    char **args;
    int status;

    if (trimmed_command == NULL || _strlen(trimmed_command) == 0) {
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
        args = (char **)malloc(2 * sizeof(char *));
        if (args == NULL)
        {
            perror("Malloc error");
            _exit(EXIT_FAILURE);
        }

        args[0] = _strdup(trimmed_command);
        args[1] = NULL;

        execve(trimmed_command, args, NULL);
        _puts("Execve error");
        _putchar('\n');
        free(args[0]);
        free(args);
        _exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}

int main() 
{
    char* line = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;

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
