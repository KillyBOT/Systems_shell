#include "shell.h"

/*
Function purpose: Iterate through the given pipe buffer. It will execute each command,
and then will chain each together so that the stdout of one of the files equals the
stdin of the next file.

Input: It will take in the run buffer that will be used, the arg buffer that
will be used, and the pipe buffer that will be used.

Output: It will not return anything

Example:
pipe_program(runBuffer,argBuffer,pipeBuffer);
*/

void pipe_program(char** runBuffer,char** argBuffer, char** pipeBuffer){

  int p,in,ifLast,oldin;

  p = 0;
  ifLast = 0;
  oldin = dup(STDIN_FILENO);

  while(pipeBuffer[p] != NULL){

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

    if(ifLast){
      dup2(oldin,STDIN_FILENO);
      close(oldin);
    }

    p++;
  }
}
