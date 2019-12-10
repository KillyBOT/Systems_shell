#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_ARGS_SIZE 256
#define SHELL_VERSION 0
#define SHELL_SUB_VERSION 10

void parse_args(char** argBuffer, char* rawIn);
void parse_semicolon(char** semiBuffer, char* rawIn);
void parse_pipe(char** pipeBuffer, char* rawIn);
void parse_arg(char** runBuffer, char** argBuffer);
int pipe_program(char** runBuffer,char** argBuffer, char** pipeBuffer);
int run_program(char** runBuffer, char** argBuffer, int in, int out);
void ch_dir(char** buffer);
