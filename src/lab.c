#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    return 0;
  }

  char **cmd_parse(char const *line)
  {
    return 0;
  }

  void cmd_free(char ** line)
  {

  }

  char *trim_white(char *line)
  {
    return 0;
  }

  bool do_builtin(struct shell *sh, char **argv)
  {
    return false;
  }


  void sh_init(struct shell *sh){

  }

  void sh_destroy(struct shell *sh){

  }

  void parse_args(int argc, char **argv){

  }








