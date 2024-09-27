/**
 * Author: Sara Martinez Soto
 * Date: Tue Sep 24 12:38:08 PM 2024
 * Description: Implementation of lab.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <pwd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "lab.h"

#define MAX_CHAR_LENGTH 20

  char *get_prompt(const char *env) {
    /* "getenv() function returns a pointer to the value in the
       environment, or NULL if there is no match.""*/
    char *prompt = getenv(env);

    if (prompt == NULL) {
        prompt = (char *) malloc(sizeof(char) * MAX_CHAR_LENGTH);
        //strcpy(prompt, "shell>"); // Watch out for buffer overflow
        strncpy(prompt, "shell>", MAX_CHAR_LENGTH); //use strncpy instead 
    } else {
        prompt = (char *) malloc(sizeof(char) * MAX_CHAR_LENGTH);
        strncpy(prompt, getenv(env), MAX_CHAR_LENGTH);
    }
    return prompt;
    free(prompt); //? 
  }

  int change_dir(char **dir)
  { 
    char *directory = dir[1];
    int returnValue = 0; 

    //Get Home directory - First attempt with getenv
    if(directory == NULL && getenv("HOME") != NULL){
      returnValue = chdir(getenv("HOME"));
      return returnValue;
    }

    //If getenv doesn't work, then attempt with getuid & getpwuid
    if(directory == NULL && getenv("HOME") == NULL){
      struct passwd *pwd = getpwuid(getuid());
      if(pwd == NULL){
        perror("cd: Failed to get home directory\n");
        return -1;
      } else {
        returnValue = chdir(pwd->pw_dir); 
        return returnValue;
      }
    }

    //chdir with given directory
    if (chdir(directory) != 0){
      printf("cd: failed to change directory\n");
    } 
    return returnValue;
  }

  char **cmd_parse(char const *line)
  {
    char *lineDuplicate = strdup(line); // Create a copy of line 
    trim_white(lineDuplicate);
    char *token = ""; 

    int argLimit = sysconf(_SC_ARG_MAX);
    char **parsedLine = (char **) malloc(sizeof(char *) * argLimit); // array of string kinda

    if(lineDuplicate == NULL){
      return NULL;
    }

    token = strtok(lineDuplicate, " ");
    int i = 0;
    while(token != NULL){
      parsedLine[i] = strdup(token);
      i++;
      token = strtok(NULL, " ");
    }
    parsedLine[i] = NULL;

    free(lineDuplicate);
    return parsedLine;
  }

  void cmd_free(char ** line)
  {
    int i = 0;
    while(line[i] != NULL){ // Each char* needs to be freed
      free(line[i]);
      i++;
    }
    free(line);
  }

  char *trim_white(char *line)
  {
    int i = 0;
    int j;

    //Iterating through line until there's no more whitespace chars 
    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'){
        i++;
    }
 
   // Shift all characters to the left and add null termination to string
    while (line[i] != '\0'){
        line[j] = line[i];
        i++;
        j++;
    }
    line[j] = '\0';

    //Remove all trailing whitespace
    i = strlen(line) - 1; 
    while(i >= 0 && isspace(line[i])){
      line[i] = '\0';//null terminated string!
      i--;
    }

    return line;
  }


  //TASK 6
  //Use strcmp for keywords like exit and cd 

  bool do_builtin(struct shell *sh, char **argv)
  {
    char cwd[1024];
    bool builtin = false; 
    
    if(argv[0] == NULL){
      return;
    }

    /*should deal with exit and EOF/ctrl-d*/
    if(strcmp(argv[0], "exit") == 0){ // TO DO: add ctrl-d?
      builtin = true; 
      sh_destroy(sh);
      exit(0);
      
    } else if (strcmp(argv[0], "cd") == 0){
      builtin = true; 
      change_dir(argv);

    } else if(strcmp(argv[0], "pwd") == 0) {
      builtin = true;
      getcwd(cwd, sizeof(cwd));
      printf("%s\n", cwd);
    } else if(strcmp(argv[0], "history") == 0) {
      builtin = true;
      //history stuff
      HIST_ENTRY **the_history_list =  history_list();
       for (int i = 0; the_history_list[i] != NULL; i++ ){
        printf("%s\n", the_history_list[i]->line);
      }

    }
    return builtin;
  }


  void sh_init(struct shell *sh){
    /* Allocate space for the shell and initialize it */
    // sh = (struct shell *)malloc(sizeof(struct shell));

    /* Initializing */
    sh->shell_is_interactive = 1;
    sh->shell_pgid = 0; 
    sh->shell_tmodes.c_iflag = 0; //idk what the termios thing is //TO DO 
    sh->shell_terminal = 1; 
    sh->prompt = NULL;
  }

  void sh_destroy(struct shell *sh){
    free(sh->prompt);
    free(sh);
  }

  void parse_args(int argc, char **argv);








