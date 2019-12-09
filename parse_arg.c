#include "shell.h"
/*
Function purpose: Parse a list of arguments, and do appropriate things for stuff
such as file redirection or piping

Input: The first argument will be the new buffer that will be execvp'd, and the
second argument will be the original parsed argument array.

Output: It won't output anything, but it will change the first input.

Example:

  char** newBuffer;

  parse_arg(newBuffer,buffer);

  execvp(newBuffer[0],newBuffer);


*/

void parse_arg(char** newBuffer, char** buffer){
	int fd = 0;
	int argP = 0;
	int newBufferP = 0;
	while(buffer[argP] != NULL){

      if(!strcmp(buffer[argP],"<")){

      	free(buffer[argP]);
        argP++;
        fd = open(buffer[argP],O_RDONLY);

        if(fd == -1){
          printf("%s: %s\n",buffer[argP],strerror(errno));
          free(newBuffer);
          exit(1);
        }

        //oldstdin = dup(stdin);
        dup2(fd,STDIN_FILENO);

      } 
      else if(!strcmp(buffer[argP],">")){

      	free(buffer[argP]);
        argP++;
        fd = open(buffer[argP],O_WRONLY | O_CREAT, 0644);

        if(fd == -1){
          printf("%s: %s\n",buffer[argP],strerror(errno));
          free(newBuffer);
          exit(1);
        }

        dup2(fd,STDOUT_FILENO);

      } else if(!strcmp(buffer[argP],">>")){

        argP++;
        fd = open(buffer[argP],O_WRONLY | O_APPEND, 0644);
        if(fd == -1) fd = creat(buffer[argP],0644);

        if(fd == -1){
          printf("%s: %s\n",buffer[argP],strerror(errno));
          free(newBuffer);
          exit(1);
        }

        dup2(fd,STDOUT_FILENO);

      } else if(!strcmp(buffer[argP],"2>")){

        argP++;
        fd = open(buffer[argP],O_WRONLY | O_APPEND, 0644);
        if(fd == -1) fd = creat(buffer[argP],0644);

        if(fd == -1){
          printf("%s: %s\n",buffer[argP],strerror(errno));
          free(newBuffer);
          exit(1);
        }

        dup2(fd,STDERR_FILENO);

      } else if(!strcmp(buffer[argP],"&>")){

        argP++;
        fd = open(buffer[argP],O_WRONLY | O_APPEND, 0644);
        if(fd == -1) fd = creat(buffer[argP],0644);

        if(fd == -1){
          printf("%s: %s\n",buffer[argP],strerror(errno));
          free(newBuffer);
          exit(1);
        }

        dup2(fd,STDERR_FILENO);
        dup2(fd,STDOUT_FILENO);

      } else {
        newBuffer[newBufferP] = buffer[argP];
        newBufferP++;
      }

      argP++;
    }

    newBuffer[newBufferP] = NULL;
}