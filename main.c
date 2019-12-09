#include "shell.h"

int main(){

  time_t t; //The current time
  int status; //The reaped values from the child process
  char* dBuf; //Current working directory buffer
  char* rawIn; //The raw input as a string
  char** argBuffer; //The first buffer, where splits happen in between semicolons
  char** buffer; //The second buffer, where splits happen in between spaces
  char** runBuffer; //The third buffer, which will be the actual command that will be issued
  DIR* d; //The current directory

  rawIn = malloc(sizeof(char) * MAX_BUFFER_SIZE);
  buffer = malloc(sizeof(char) * MAX_ARGS_SIZE);
  dBuf = malloc(pathconf(".", _PC_PATH_MAX));
  argBuffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
  runBuffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);

  time(&t);

  printf("Welcome to KShell %d.%d\nCurrent time is %s\n", SHELL_VERSION, SHELL_SUB_VERSION, ctime(&t));

  while(1){

    printf("\033[1;31m%s\033[0m$ ",getcwd(dBuf,pathconf(".", _PC_PATH_MAX))); //Print current working directory, and signifier

    fgets(rawIn,MAX_BUFFER_SIZE,stdin);
    rawIn[strlen(rawIn)-1] = '\0';

    parse_semicolon(argBuffer,rawIn);

    for(int x = 0; argBuffer[x] != NULL; x++){

      parse_args(buffer,argBuffer[x]);

      /*int p = 0;
      while(buffer[p] != NULL){
        printf("[%s] ", buffer[p]);
        p++;
      }
      printf("\n");*/

      if(!strcmp(buffer[0], "exit")){

        printf("Closing shell... See you next time :)\n");

        free(rawIn);
        free(buffer);
        free(argBuffer);
        free(dBuf);

        exit(0);

      } else if(!strcmp(buffer[0], "cd")){
        ch_dir(buffer);
      } else {
        status = run_program(runBuffer,buffer);
        //printf("Child returned. Return signal: %d Term signal: %d\n", WEXITSTATUS(status), WTERMSIG(status));
      }
      free(buffer);
      free(runBuffer);
    }
  }


}
