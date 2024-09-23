#include <stdio.h>
#include <unistd.h>
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

  printf("Hello World!\n");
}
