#include "shell.h"

int main(){

  time_t t; //The current time
  int status; //The reaped values from the child process
  char* dBuf; //Current working directory buffer
  char* rawIn; //The buffer for the raw input
  char** buffer; //The buffer for the parsed input
  DIR* d; //The current directory

  rawIn = malloc(sizeof(char) * MAX_BUFFER_SIZE);
  buffer = malloc(sizeof(char) * MAX_ARGS_SIZE);
  dBuf = malloc(pathconf(".", _PC_PATH_MAX));

  time(&t);

  printf("Welcome to KShell %d.%d\nCurrent time is %s\n", SHELL_VERSION, SHELL_SUB_VERSION, ctime(&t));

  while(1){

    printf("\033[1;34m%s\033[0m$ ",getcwd(dBuf,pathconf(".", _PC_PATH_MAX))); //Print current working directory, and signifier

    fgets(rawIn,MAX_BUFFER_SIZE,stdin);
    rawIn[strlen(rawIn)-1] = '\0';

    parse_args(buffer,rawIn);

    /*int p = 0;
    while(buffer[p] != NULL){
      printf("%s", buffer[p]);
      p++;
    }
    printf("\n");*/

    if(!strcmp(buffer[0], "exit")){
      printf("Closing shell... See you next time :)\n");

      free(rawIn);
      free(buffer);
      free(dBuf);

      return 0;
    }

    status = run_program(buffer);
    printf("Child returned. Return signal: %d Term signal: %d\n", WEXITSTATUS(status), WTERMSIG(status));
    if(!WEXITSTATUS(status))printf("Error running program!\n");
  }


}
