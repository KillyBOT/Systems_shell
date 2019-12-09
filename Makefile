ifeq ($(DEBUG),true)
	CC = gcc -g
else
	CC = gcc
endif

OBJECTS = main.o parse_args.o run_program.o ch_dir.o parse_semicolon.o parse_arg.c parse_pipe.c pipe_program.c

all: $(OBJECTS) shell.h
	$(CC) -o KShell $(OBJECTS)

main.o: main.c shell.h
	$(CC) -c main.c

parse_args.o: parse_args.c shell.h
	$(CC) -c parse_args.c

run_program.o: run_program.c shell.h
	$(CC) -c run_program.c

ch_dir.o: ch_dir.c shell.h
	$(CC) -c ch_dir.c

parse_semicolon.o: parse_semicolon.c shell.h
	$(CC) -c parse_semicolon.c

parse_arg.o: parse_arg.c shell.h
	$(CC) -c parse_arg.c

parse_pipe.o: parse_pipe.c shell.h
	$(CC) -c parse_pipe.c

pipe_program.o: pipe_program.c shell.h
	$(CC) -c pipe_program.c

run:
	./KShell

valgrind:
	valgrind --leak-check=yes ./KShell
