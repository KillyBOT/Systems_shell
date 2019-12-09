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

    int argP = 0;
    int newBufferP = 0;
    //int oldstdin = STDIN_FILENO;
    //int oldstdout = stdout;
    int fd = 0;
    char** newBuffer = malloc(sizeof(char) * MAX_ARGS_SIZE);

    while(buffer[argP] != NULL){

      if(!strcmp(buffer[argP],"<")){

        argP++;
        fd = open(buffer[argP],O_RDONLY);

        if(fd == -1){
          printf("%s: %s\n",buffer[argP],strerror(errno));
          free(newBuffer);
          exit(1);
        }

        //oldstdin = dup(stdin);
        dup2(fd,STDIN_FILENO);

      } else if(!strcmp(buffer[argP],">")){
        argP++;
        fd = open(buffer[argP],O_WRONLY | O_CREAT, 0644);

        if(fd == -1){
          printf("%s: %s\n",buffer[argP],strerror(errno));
          free(newBuffer);
          exit(1);
        }

        //oldstdin = dup(stdin);
        dup2(fd,STDOUT_FILENO);
      }
      else {
        newBuffer[newBufferP] = buffer[argP];
        newBufferP++;
      }
      argP++;
    }

    newBuffer[newBufferP] = NULL;
    newBufferP++;

    if(execvp(newBuffer[0],newBuffer) < 0) {
      printf("%s: %s\n",buffer[0],strerror(errno));
      free(newBuffer);
      exit(1);
    }

  }
}
