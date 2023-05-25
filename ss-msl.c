#include "shell.h"
#define CMD_MAX_LEN 1024

/**
 * main - This loop over the all the functions below forever
 * @argc: to count the number of args
 * @argv: to store the strings
 * on SUCCESS return EXIT_SUCCESS
*/

int main(void)
{
  char cmd[BUFFER_SIZE];
  bool fromPipe = false;
  char *prompt = "sam@munaray> ";
  pid_t child_pid;
  int wstatus;
  ssize_t bytes;

  while (1 && !fromPipe)
  {
    if (isatty(STDIN_FILENO) == 0)
      fromPipe = true;
    write(STDOUT_FILENO, prompt, 2);

    bytes = get_input(cmd);
    if (bytes == -1)
    {
      perror("Error (get_input)");
      free(cmd);
      exit(EXIT_FAILURE);
    }
    if (cmd[bytes - 1] == '\n')
      cmd[bytes - 1] = '\0';
    child_pid = fork();
    if (child_pid == -1)
    {
      perror("Error (fork)");
      exit(EXIT_FAILURE);
    }
    if (child_pid == 0)
      _executeCommand(cmd, NULL);
    if (waitpid(child_pid, &wstatus, 0) == -1)
    {
      perror("Error (wait)");
      exit(EXIT_FAILURE);
    }
    }
    free(cmd);
    return (0);
}


/**
 * executeCommand - This execute the user's input
 * @cmd: The cmd to be executed is stored here
 */

void _executeCommand(char *args, char **argv)
{
    struct stat *statbuf;
    int argc;
    char *exe;
    struct stat statbuf;

    argv = splitString(args, ' ', &argc);
    if (argc == 0)
    {
        char *error_msg = "No command specified.\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        exit(EXIT_FAILURE);
    }
    exe = argv[0];
    if (stat(exe, &statbuf) == -1)
    {
        perror("Error (stat)");
        exit(EXIT_FAILURE);
    }
    execve(exe, argv, NULL);
    perror("Error (execve)");
    exit(EXIT_FAILURE);
}
