#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


#include "../src/lab.h"

int main(int argc, char ** argv)
{
  
  int opt; 
  struct shell sh;
  char * prompt = "";
  char *line;

  /*Task 3: printing shell version*/
  while ((opt = getopt(argc, argv, "v")) != -1) 
  {
    switch (opt) 
  {
    case 'v':
      printf("Version %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
      break;
    default:
      abort();
    } 
  }

  

  //sh_init(&sh);
  prompt = get_prompt("MY_PROMPT");
  //sh.prompt = prompt;

  //printf("Hello World!\n");

  /* Dealing with the user's input */
  using_history();

  while ((line=readline(prompt))){
      printf("%s\n",line);
      add_history(line);
      free(line);
  }

  

  

}
