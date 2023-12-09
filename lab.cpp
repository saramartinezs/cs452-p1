#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "lab.h"

#define UNUSED(x) (void)(x)

char *getVersion(void)
{
  char *version = (char *)malloc(MAX_VERSION_STRING);
  snprintf(version, MAX_VERSION_STRING, "%d.%d", lab_VERSION_MAJOR, lab_VERSION_MINOR);
  return version;
}

int *leakyFunction(int a)
{
  int *rval = (int *)malloc(sizeof(int));
  rval = (int *)malloc(sizeof(int));
  *rval = a;
  return rval;
}

int segfault(void)
{
  // add volatile because clang will optimize out the segfault
  volatile int *foo = nullptr;
  int bar = *foo;
  return bar;
}

void outOfBounds(void)
{
  int arr[5] = {0, 1, 2, 3, 4};
  int i = 0;
  for (i = 0; i < 6; i++)
    {
      arr[i] = i;
    }
  UNUSED(arr);
}
