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
#define SHELL_SUB_VERSION 4

void parse_args(char** buffer, char* rawIn);
int run_program(char** buffer);
void ch_dir(char** buffer);
