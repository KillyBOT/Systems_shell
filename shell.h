#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 512
#define MAX_ARGS_SIZE 64
#define SHELL_VERSION 0
#define SHELL_SUB_VERSION 3

void parse_args(char** buffer, char* rawIn);
int run_program(char** buffer);
