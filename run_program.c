#include "shell.h"

/*
Function purpose: Create a seperate child process, run that child process, wait
until that child is finished, and return the reaped data from that process. It
will also pipe to certain files if noted by the status.

Input: It will take in the buffer that will be used when running, the argument
buffer, whether to set the input and output (if status)

Output: It will return the int that was reaped from the child process

Example:
printf("Program ran. Reaped value %d.",run_program(buffer));
*/
int run_program(char** runBuffer, char** argBuffer, int in, int ifLast){
  int ifParent;
  int childStatus;
  char* f1 = "a";
  char* f2 = "b";
  int pipefd[2];

  pipe(pipefd);
  //printf("%d %d\n", pipefd[PIPE_READ],pipefd[PIPE_WRITE]);
  ifParent = fork();

  if(ifParent){
    close(pipefd[PIPE_WRITE]);
    waitpid(ifParent,&childStatus,0);
    //return childStatus;
    if(ifLast){
      close(pipefd[PIPE_READ]);
      return STDIN_FILENO;
    }
    else return pipefd[PIPE_READ];

  } else {

    /*for(int p = 0; buffer[p] != NULL; p++) printf("[%s] \n", buffer[p]);
    printf("\n");*/
    //printf("%d %d\n", currentFile, status);

    /*if((status & REPLACE_IN)) {
      int in;

      if(currentFile) in = open(f1,O_RDONLY);
      else in = open(f2,O_RDONLY);

      dup2(in,STDIN_FILENO);
    }

    if((status & REPLACE_OUT)) {
      int out;

      if(currentFile) out = creat(f2,0644);
      else out = creat(f1,0644);

      dup2(out,STDOUT_FILENO);
    }*/


    dup2(in,STDIN_FILENO);
    if(!ifLast)dup2(pipefd[PIPE_WRITE],STDOUT_FILENO);
    parse_arg(runBuffer,argBuffer);

    if(execvp(runBuffer[0],runBuffer) < 0) {
      printf("%s: %s\n",runBuffer[0],strerror(errno));
      exit(1);
    }

  }
}
