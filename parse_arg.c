#include "shell.h"
/*
Function purpose: Parse a list of arguments, and do appropriate things for stuff
such as file redirection or piping.

Input: The first argument will be the new buffer that will be execvp'd, and the
second argument will be the original parsed argument array.

Output: It won't output anything, but it will change the first input.

Example:

  char** newBuffer;

  parse_arg(newBuffer,buffer);

  execvp(newBuffer[0],newBuffer);
*/

void parse_arg(char** runBuffer, char** argBuffer){
	int fd = 0;
	int argP = 0;
	int runBufferP = 0;
	while(argBuffer[argP] != NULL){

      if(!strcmp(argBuffer[argP],"<")){

        argP++;
        fd = open(argBuffer[argP],O_RDONLY);

        if(fd == -1){
          printf("%s: %s\n",argBuffer[argP],strerror(errno));
          exit(1);
        }

        dup2(fd,STDIN_FILENO);
				close(fd);
      }
			else if(!strcmp(argBuffer[argP],">")){

        argP++;
        fd = open(argBuffer[argP],O_WRONLY | O_TRUNC | O_CREAT, 0644);

        if(fd == -1){
          printf("%s: %s\n",argBuffer[argP],strerror(errno));
          exit(1);
        }

        dup2(fd,STDOUT_FILENO);
				close(fd);
			} else if(!strcmp(argBuffer[argP],">>")){

        argP++;
        fd = open(argBuffer[argP],O_WRONLY | O_APPEND);
        if(fd == -1) fd = creat(argBuffer[argP],0644);

        if(fd == -1){
          printf("%s: %s\n",argBuffer[argP],strerror(errno));
          exit(1);
        }

        dup2(fd,STDOUT_FILENO);
				close(fd);

      } else if( !strcmp(argBuffer[argP],"2>") ){

        argP++;
        fd = open(argBuffer[argP],O_WRONLY | O_TRUNC | O_CREAT, 0644);

        if(fd == -1){
          printf("%s: %s\n",argBuffer[argP],strerror(errno));
          exit(1);
        }

        dup2(fd,STDERR_FILENO);
				close(fd);

      } else if(!strcmp(argBuffer[argP],"&>")){

        argP++;
        fd = open(argBuffer[argP],O_WRONLY | O_TRUNC | O_CREAT, 0644);

        if(fd == -1){
          printf("%s: %s\n",argBuffer[argP],strerror(errno));
          exit(1);
        }

        dup2(fd,STDERR_FILENO);
        dup2(fd,STDOUT_FILENO);
				close(fd);

      } else if(!strcmp(argBuffer[argP],"2>>")){

        argP++;
        fd = open(argBuffer[argP],O_WRONLY | O_APPEND);
				if(fd == -1) fd = creat(argBuffer[argP],0644);

        if(fd == -1){
          printf("%s: %s\n",argBuffer[argP],strerror(errno));
          exit(1);
        }

        dup2(fd,STDERR_FILENO);
				close(fd);

      } else if(!strcmp(argBuffer[argP],"&>>")){

        argP++;
        fd = open(argBuffer[argP],O_WRONLY | O_APPEND);
				if(fd == -1) fd = creat(argBuffer[argP],0644);

        if(fd == -1){
          printf("%s: %s\n",argBuffer[argP],strerror(errno));
          exit(1);
        }

        dup2(fd,STDERR_FILENO);
        dup2(fd,STDOUT_FILENO);
				close(fd);

      } else {
        runBuffer[runBufferP] = argBuffer[argP];
        runBufferP++;
      }

      argP++;
    }

    argBuffer[runBufferP] = NULL;
}
