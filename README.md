# KShell

## Features

*Simple command reading and executing
	*cd also works
	*Spacing between arguments doesn't matter!
*Ability to issue multiple commands using ;
*Ability to redirect the input or output of a program using < or > respectively
	*Other file redirection commands such as >> or &> work as well
*Ability to pipe the output of one program into another program using |
*Username, computer name, and current directory are listed
	*Note that this may not work on platforms outside of Linux

## Unimplemented features

*Ability to scroll through previous commands using arrow keys
*Ability to auto complete arguments using tab

## Bugs

There are no bugs that I know of, so if you find any please tell me!

If I were to guess, the place that would have the most bugs would probably be the file redirection.

## Header Functions

'''
void parse_args(char** argBuffer, char* rawIn);
void parse_semicolon(char** semiBuffer, char* rawIn);
void parse_pipe(char** pipeBuffer, char* rawIn);
void parse_arg(char** runBuffer, char** argBuffer);
void pipe_program(char** runBuffer,char** argBuffer, char** pipeBuffer);
int run_program(char** runBuffer, char** argBuffer, int in, int ifLast);
void ch_dir(char** buffer);
'''