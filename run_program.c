#include "shell.h"

/*
Function purpose: Create a seperate child process, run that child process, wait
until that child is finished, and return the reaped data from that process

Input: It will take in the parsed input string

Output: It will return the int that was reaped from the child process

Example:
printf("Program ran. Reaped value %d.",run_program(buffer));
*/
int run_program(char** buffer){
  int ifParent;
  int status;

  ifParent = fork();

  if(ifParent){
    waitpid(ifParent,&status,0);
    return status;
  } else {    

    char** newBuffer = malloc(sizeof(char) * MAX_ARGS_SIZE);

    /*for(int p = 0; buffer[p] != NULL; p++) printf("[%s] \n", buffer[p]);
    printf("\n");*/

    parse_arg(newBuffer,buffer);

    if(execvp(newBuffer[0],newBuffer) < 0) {
      printf("%s: %s\n",newBuffer[0],strerror(errno));
      free(newBuffer);
      exit(1);
    }

  }
}
