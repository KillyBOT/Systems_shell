#include "shell.h"
/*
Function purpose: Parse a raw string, split the string every time it sees a
vertical slash, and place those pieces into the given buffer. This will be used
for piping.

Input: The first argument is the buffer that will be written to. It will be an
array of pointers, with a size of 64. The second argument is the raw input,
as a string.

Output: It won't output anything, but it will change the first input

Example:

  char* rawIn = "ls | cat"
  char** bufferedIn;

  parse_pipe(bufferedIn, rawIn);

  //bufferedIn should equal ["ls","cat",...]
*/

void parse_pipe(char** pipeBuffer, char* rawIn){
    int p = 0;

    while(rawIn != NULL && *rawIn != '\0'){
      pipeBuffer[p] = strsep(&rawIn,"|");
      while(pipeBuffer[p] != NULL && *pipeBuffer[p] != '\0' && *pipeBuffer[p] == ' ') pipeBuffer[p]++;
      while(rawIn != NULL && *rawIn != '\0' && *rawIn == ' ') rawIn++;
      p++;
    }

    pipeBuffer[p] = NULL;
}
