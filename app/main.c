#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
char *line;


#include "../src/lab.h"

int main(int argc, char ** argv)
{
  
  int opt;

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
  using_history();
  while ((line=readline("$"))){
      printf("%s\n",line);
      add_history(line);
      free(line);
  }
  printf("Hello World!\n");
}
