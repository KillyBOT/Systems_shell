#include "shell.h"

int main(){

  time_t t;
  int running;
  char* rawIn;
  char** buffer;

  rawIn = malloc(sizeof(char) * MAX_BUFFER_SIZE);
  buffer = malloc(sizeof(char) * MAX_ARGS_SIZE);
  running = 1;

  time(&t);

  printf("Welcome to KShell %d.%d\nCurrent date is %s\n", SHELL_VERSION, SHELL_SUB_VERSION, ctime(&t));

  while(running){
    printf("$");

    fgets(rawIn,MAX_BUFFER_SIZE,stdin);

    printf("%s\n", rawIn);
    parse_args(buffer,rawIn);

    running = 0;
  }

  printf("Closing shell...\n");

  free(rawIn);
  free(buffer);

  return 0;
}
