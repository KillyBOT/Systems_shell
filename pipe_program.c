#include "shell.h"

/*
Function purpose: Iterate through the given pipe buffer. Execute each command,
and then chain each together so that the stdout of one of the files equals the
stdin of the next file

Input: It will take in the run buffer that will be used, the arg buffer that
will be used, and the pipe buffer

Output: It will return the int that was reaped from the final

Example:
printf("Program ran. Reaped value %d.",pipe_program(argBuffer,buffer));
*/

int pipe_program(char** runBuffer,char** argBuffer, char** pipeBuffer){

  int p = 0;
  int currentFile = 0;
  int status = 2;
  int in = STDOUT_FILENO;
  int out = -1;
  int ifLast = 0;
  int oldin = dup(STDIN_FILENO);
  int pipefd[2];
  char copy_buffer[1];

  while(pipeBuffer[p] != NULL){
    //printf("%d %d %d\n", currentFile,in,out);

    /*if(pipeBuffer[p + 1] == NULL) {
      if(p == 0) status = 0;
      else status = REPLACE_IN;
    }*/
    if(pipeBuffer[p + 1] == NULL) ifLast = 1;

    parse_args(argBuffer,pipeBuffer[p]);

    if(!strcmp(argBuffer[0],"cd")){
      ch_dir(argBuffer);
      in = STDIN_FILENO;
    } else {
      in = run_program(runBuffer,argBuffer,STDIN_FILENO,ifLast);
      dup2(in,STDIN_FILENO);
      close(in);
    }
    /*int n = 0;
    while(argBuffer[n] != NULL){
      printf("[%s] ", argBuffer[n]);
      n++;
    }
    printf("\n");*/
    //pipe(pipefd);

    //tempPipeFD = dup(pipefd[1]);

    if(pipeBuffer[p+1] == NULL){
      //printf("%d\n", in);
      //close(in);
      //close(STDIN_FILENO);
      dup2(oldin,STDIN_FILENO);
    }

    /*if(pipeBuffer[p + 1] != NULL){
      status = REPLACE_OUT | REPLACE_IN;
      currentFile = !currentFile;
    }*/

    p++;
  }

  //remove("a");
  //remove("b");
}
