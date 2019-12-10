#include "shell.h"

/*
Function purpose: Create a seperate child process, run that child process, wait
until that child is finished, and return the reaped data from that process

Input: It will take in the buffer that will be used when running, the argument
buffer, and the file to set stdout to.

Output: It will return the int that was reaped from the child process

Example:
printf("Program ran. Reaped value %d.",run_program(buffer));
*/
int run_program(char** runBuffer, char** buffer, int in, int out){
  int ifParent;
  int status;

  ifParent = fork();

  if(ifParent){
    waitpid(ifParent,&status,0);
    return status;
  } else {

    /*for(int p = 0; buffer[p] != NULL; p++) printf("[%s] \n", buffer[p]);
    printf("\n");*/

    dup2(in,STDIN_FILENO);
    dup2(out,STDOUT_FILENO);

    parse_arg(runBuffer,buffer);
    //printf("\n%d %d\n",in,out);

    if(execvp(runBuffer[0],runBuffer) < 0) {
      printf("%s: %s\n",runBuffer[0],strerror(errno));
      exit(1);
    }

  }
}
