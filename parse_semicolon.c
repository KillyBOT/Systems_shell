#include "shell.h"

/*
Function purpose: Parse a raw string, split the string every time it sees a
semicolon, and place those pieces into the given buffer. This allows for multiple
commands to be written in one line.

Input: The first argument is the buffer that will be written to. It will be an
array of pointers, with a size of 64. The second argument is the raw input,
as a string.

Output: It won't output anything, but it will change the first input

Example:

  char* rawIn = "This is a test"
  char** bufferedIn;

  parse_args(bufferedIn, rawIn);

  //bufferedIn should equal ["This","is","a","test",NULL,...]
*/

void parse_semicolon(char** buffer,char* rawIn){
    int p = 0;

    while(rawIn != NULL && *rawIn != '\0'){
      buffer[p] = strsep(&rawIn,";");
      while(buffer[p] != NULL && *buffer[p] == ' ') buffer[p]++;
      while(rawIn != NULL && *rawIn != '\0' && *rawIn == ' ') rawIn++;
      p++;
    }

    buffer[p] = NULL;
}
