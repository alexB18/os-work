
# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = gcc
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: server

# To create the executable file count we need the object file(s)
# part1.o:
#
server:  Entry.o main.o
	$(CC) $(CFLAGS) -o server Entry.o main.o

# Rule for testing just the Entry object
entry_test: Entry.o entry_test.o
	$(CC) $(CFLAGS) -o entry_test Entry.o entry_test.o


# To create the object file entries.o, we need the source
# file(s) entries.c and the header file entries.h:
#
Entry.o: Entry.c
	$(CC) $(CFLAGS) -c Entry.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

entry_test.o: entry_test.c
	$(CC) $(CFLAGS) -c entry_test.c

clean: 
	$(RM) server log.txt *.o *~

# To run valgrind, type 'make val-file'
# Valgrind will run a leak check and store the
# results in log.txt
val: server
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./server > log.txt 2>&1


