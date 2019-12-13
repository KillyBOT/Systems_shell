#include "shell.h"

/*
Function purpose: Creates a pipe, and then forks. The parent waits for the child
program, and the child runs, sending its output to the pipe, which the parent
will pick up.

Input: It will take in the buffer that will be used when running, the argument
buffer, the file descriptor of what to set STDIN to, and if it's the last
program in the chain

Output: It will return the file descriptor of the read end of the pipe it created

Example:
int nextIn = run_program(runBuffer,argBuffer,STDIN_FILENO,0);
*/
int run_program(char** runBuffer, char** argBuffer, int in, int ifLast){
  int ifParent, childStatus, pipefd[2];

  pipe(pipefd);
  //printf("%d %d\n", pipefd[PIPE_READ],pipefd[PIPE_WRITE]);
  ifParent = fork();

  if(ifParent){
    close(pipefd[PIPE_WRITE]);
    waitpid(ifParent,&childStatus,0);

    return pipefd[PIPE_READ];
  } else {

    close(pipefd[PIPE_READ]);

    dup2(in,STDIN_FILENO);

    if(!ifLast){
      dup2(pipefd[PIPE_WRITE],STDOUT_FILENO);
    }

    parse_arg(runBuffer,argBuffer);

    if(execvp(runBuffer[0],runBuffer) < 0) {
      printf("%s: %s\n",runBuffer[0],strerror(errno));
      exit(1);
    }

  }
}
