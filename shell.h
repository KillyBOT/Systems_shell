#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#define MAX_STRING_SIZE 128
#define SHELL_VERSION 0
#define SHELL_SUB_VERSION 1

char** parseArgs(char* buffer);
