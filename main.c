#include "shell.h"

int main(){

  time_t t;
  char* buffer = malloc(sizeof(char) * MAX_STRING_SIZE);

  time(&t);

  printf("Welcome to KShell %d.%d\nCurrent date is %s\n", SHELL_VERSION, SHELL_SUB_VERSION, ctime(&t));

  free(buffer);

  return 0;
}
