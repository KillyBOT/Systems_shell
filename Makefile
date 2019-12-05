ifeq ($(DEBUG),true)
	CC = gcc -g
else
	CC = gcc
endif

OBJECTS = main.o parse_args.o run_program.o ch_dir.o

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

run:
	./KShell

valgrind:
	valgrind --leak-check=yes ./KShell
