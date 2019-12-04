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
    wait(&status);
    return status;
  } else {
    if(execvp(buffer[0],buffer) < 0) return -1;

  }
}
