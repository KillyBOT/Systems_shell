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
  int oldstdout = dup(STDOUT_FILENO);
  int oldstdin = dup(STDIN_FILENO);
  int in = oldstdin;
  int out = oldstdout;

  while(pipeBuffer[p] != NULL){

    if(pipeBuffer[p + 1] == NULL) {
      out = oldstdout;
    }
    else{
      out = creat("temp",0644);
    }

    parse_args(argBuffer,pipeBuffer[p]);

    int n = 0;
    while(argBuffer[n] != NULL){
      printf("[%s] ", argBuffer[n]);
      n++;
    }
    printf("\n");

    run_program(runBuffer,argBuffer,in,out);

    if(pipeBuffer[p + 1] != NULL){
      in = out;
    }
    p++;
  }
}
