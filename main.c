

#include "shell.h"

int main(){

  time_t t; //The current time
  int status; //The reaped values from the child process
  char* dBuf; //Current working directory buffer
  char uName[MAX_BUFFER_SIZE]; //Username buffer
  char cName[MAX_BUFFER_SIZE]; //Computer name buffer
  char* rawIn; //The raw input as a string
  char** semiBuffer; //The first buffer, where splits happen in between semicolons
  char** pipeBuffer; //The second buffer, where splits happen between vertical slashes
  char** argBuffer; //The third buffer, where splits happen between spaces
  char** runBuffer; //The fourth buffer, which will be the actual command that will be issued to execvp

  rawIn = malloc(sizeof(char) * MAX_BUFFER_SIZE);
  dBuf = malloc(pathconf(".", _PC_PATH_MAX));
  semiBuffer = malloc(sizeof(char) * MAX_ARGS_SIZE);
  pipeBuffer = malloc(sizeof(char) * MAX_ARGS_SIZE);
  argBuffer = malloc(sizeof(char) * MAX_ARGS_SIZE);
  runBuffer = malloc(sizeof(char) * MAX_ARGS_SIZE);

  time(&t);
  getlogin_r(uName,LOGIN_NAME_MAX);
  gethostname(cName,HOST_NAME_MAX);

  printf("Welcome to KShell %d.%d\nCurrent time is %s\n", SHELL_VERSION, SHELL_SUB_VERSION, ctime(&t));

  while(1){

    printf("\033[1;32m%s@%s\033[0m:\033[1;31m%s\033[0m$ ",uName,cName,getcwd(dBuf,pathconf(".", _PC_PATH_MAX))); //Print current working directory, and signifier

    fgets(rawIn,MAX_BUFFER_SIZE,stdin);
    rawIn[strlen(rawIn)-1] = '\0';

    parse_semicolon(semiBuffer,rawIn);

    for(int x = 0; semiBuffer[x] != NULL; x++){ //Parse each semicolon arg

      parse_pipe(pipeBuffer,semiBuffer[x]);
      /*for(int n = 0; pipeBuffer[n] != NULL; n++){
        printf("[%s] ", pipeBuffer[n]);
      }
      printf("\n");*/

      if(!strcmp(pipeBuffer[0], "exit")){

        printf("Closing shell... See you next time :)\n\n\n");

        free(rawIn);
        free(semiBuffer);
        free(pipeBuffer);
        free(argBuffer);
        free(runBuffer);
        free(dBuf);

        exit(0);

      } else {
        pipe_program(runBuffer,argBuffer,pipeBuffer);
        //printf("Child returned. Return signal: %d Term signal: %d\n", WEXITSTATUS(status), WTERMSIG(status));
      }

    }
  }

}
