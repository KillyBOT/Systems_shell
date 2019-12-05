/*
Function purpose: Parse a raw string, split the string every time it sees a
space, and place those pieces into the given buffer.

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

void parse_semicolon(char** buffer){
  void parse_args(char** buffer, char* rawIn){

    int p = 0;

    while(rawIn != NULL){
      buffer[p] = strsep(&rawIn,";");
      p++;
      //printf("%s\n", rawIn);
    }

    buffer[p] = NULL;
  }
}
