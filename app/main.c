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

struct job {
    int jobId;
    pid_t pid;
    char *command;
    struct job *next;
    bool done; 
};

struct job *jobList = NULL;
int jobCounter = 0;

bool is_background(char *line);
void add_job(pid_t pid, char *command);
void check_background_jobs();
void print_jobs();

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
  sh->prompt = prompt;

  /* Dealing with the user's input */
  using_history();

  while ((line=readline(prompt))){
      add_history(line);
      line = trim_white(line);

      bool isBackgroundJob = is_background(line);

      char **commandParsed = cmd_parse(line);
      
      if(!do_builtin(sh, commandParsed)){
        pid_t pid = fork();

        if (pid < 0) {
          // Error handling
          fprintf(stderr, "Fork failed\n");
          exit(1);
        } else if (pid == 0) { 
          // Child process
          pid_t child = getpid();
          setpgid(child, child);
          
          if (!isBackgroundJob) {
            tcsetpgrp(sh->shell_terminal, child); 
          }
          //tcsetpgrp(sh->shell_terminal, child); //transfers terminal control to the child process
          signal (SIGINT, SIG_DFL);
          signal (SIGQUIT, SIG_DFL);
          signal (SIGTSTP, SIG_DFL);
          signal (SIGTTIN, SIG_DFL);
          signal (SIGTTOU, SIG_DFL);

          if(commandParsed[0] == NULL) { //EOF/CTRL+D
            free(line);
            cmd_free(commandParsed);
            break;
          }
          execvp( commandParsed[0], commandParsed);
        } else {
          // Parent process
          if (isBackgroundJob) {
            add_job(pid, line); 
          } else {
            int status;
            waitpid(pid, &status, 0);  // Wait for child process to finish
            tcsetpgrp(sh->shell_terminal, sh->shell_pgid);  // Reclaiming terminal control after child is done
          }
        }
     
      }
      check_background_jobs();
      cmd_free(commandParsed);
      free(line);
      printf("\n");
  }
  sh_destroy(sh);

}

/**
 * @brief Checks if the command is a background job. 
 * Returns true and removes ampersand if it is 
 * @param line The line that will be checked
 * @return Returns true if the process should be run in the background
 */
bool is_background(char *line) {
    int len = strlen(line);
    // Trim trailing spaces.
    line = trim_white(line);

    //Removing ampersand
    if (len > 0 && line[len - 1] == '&') {
        line[len - 1] = '\0'; 
        line = trim_white(line);
        return true; 
    }
    return false;  
}

/**
 * @brief Adds a job to the job list
 * 
 * @param pid The pid of the job to add
 * @param command The command of the job
 */
void add_job(pid_t pid, char *command) {
    struct job *newJob = (struct job *)malloc(sizeof(struct job));
    newJob->jobId = jobCounter++;
    newJob->pid = pid;
    newJob->command = strdup(command);
    newJob->next = jobList;
    jobList = newJob;
    newJob->done = false; 

    printf("[%d] %d %s\n", newJob->jobId, newJob->pid, newJob->command);
}

/**
 * @brief Checks the status of the current background jobs 
 * If a process has been completed, it prints out information 
 */
void check_background_jobs() {
    struct job **curr = &jobList;
    while (*curr) {
        int status;
        pid_t result = waitpid((*curr)->pid, &status, WNOHANG);
        if (result == 0) {
          // Process is still running...
          curr = &((*curr)->next);
        } else if (result > 0) {
          // Process has finished.
          printf("[%d] Done %s\n", (*curr)->jobId, (*curr)->command);
          (*curr)->done = true;
          struct job *finishedJob = *curr;
          *curr = finishedJob->next;
          free(finishedJob->command);
          free(finishedJob);
          //curr = &((*curr)->next); // does not work
        } else {
          perror("waitpid");
        }
    }
}

/**
 * @brief Should print out a summary of the background jobs
 */
void print_jobs() {
    struct job *curr = jobList;
    while (curr) {
        if (curr->done == false) {
            printf("[%d] %d Running %s &\n", curr->jobId, curr->pid, curr->command);
        } else if (curr->done == true) {
            printf("[%d] Done %s &\n", curr->jobId, curr->command);
        }
        curr = curr->next;
    }
}