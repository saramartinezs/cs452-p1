/**
 * Author: Sara Martinez Soto
 * Date: Tue Sep 24 12:38:08 PM 2024
 * Description: Simple shell program
*/
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <signal.h>



#include "../src/lab.h"

int main(int argc, char ** argv)
{
  
  int opt; 
  struct shell *sh = (struct shell *)malloc(sizeof(struct shell));
  char * prompt = "";
  char *line;

  /*Task 3: printing shell version*/
  while ((opt = getopt(argc, argv, "v")) != -1) {
    switch (opt) {
    case 'v':
      printf("Version %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
      break;
    default:
      abort();
    } 
  }

  sh_init(sh);
  prompt = get_prompt("MY_PROMPT");

  /* Dealing with the user's input */
  using_history();

  while ((line=readline(prompt))){
      add_history(line);
      line = trim_white(line);

      char **commandParsed = cmd_parse(line);
      // do_builtin(sh, commandParsed);
      if(!do_builtin(sh, commandParsed)){
        pid_t pid;
        pid = fork();

        if (pid < 0) {
          // Error handling
          fprintf(stderr, "Fork failed\n");
          exit(1);
        } else if (pid == 0) { 
          // Child process
          // printf("In child process\n");
          pid_t child = getpid();
          setpgid(child, child);
          tcsetpgrp(sh->shell_terminal, child); //transfers terminal control to the child process
          signal (SIGINT, SIG_DFL);
          signal (SIGQUIT, SIG_DFL);
          signal (SIGTSTP, SIG_DFL);
          signal (SIGTTIN, SIG_DFL);
          signal (SIGTTOU, SIG_DFL);
          if(commandParsed[0] == NULL) {
            continue;
          }
          execvp( commandParsed[0], commandParsed);
          
        } else {
          // Parent process
          // printf("In parent process\n");
          int *status = 0; 
          waitpid(pid, status, 0); // Wait for child process to finish
          tcsetpgrp(sh->shell_terminal, sh->shell_pgid); // Reclaiming terminal control after child is done
          // printf("done waiting\n");
        }
     
      }
      
      cmd_free(commandParsed);
      free(line);
      printf("\n");
  }

  free(sh);

}
