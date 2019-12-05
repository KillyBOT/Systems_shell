#include "shell.h"

/*
Function purpose: Change the directory of the parent process

Input: It will take in the parsed input string

Output: It won't output anything, but will specify if there's an error

Example:
ch_dir(buffer);
*/

void ch_dir(char** buffer){
  int p = 1;
  char newDir[MAX_BUFFER_SIZE] = "";
  //printf("test\n");

  for(int p = 1; buffer[p] != NULL; p++){
    strcat(newDir,buffer[p]);
    if(buffer[p+1] != NULL)strcat(newDir," ");
  }
  if(chdir(newDir) < 0) printf("%s: %s: %s\n",buffer[0],newDir,strerror(errno));

}
