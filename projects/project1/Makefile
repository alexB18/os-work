#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

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
default: pseudo-shell val

no-val: pseudo-shell

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
pseudo-shell:  command.o main.o
	$(CC) $(CFLAGS) -o pseudo-shell command.o main.o

# To create the object file command.o, we need the source
# files command.c, command.h:
#
command.o:  command.c command.h 
	$(CC) $(CFLAGS) -c command.c

# To create the object file main.o, we need the source files
# main.c and main.h:
#
main.o:  main.c 
	$(CC) $(CFLAGS) -c main.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) pseudo-shell log.txt *.o *~

# To run valgrind, type 'make val'
# Valgrind will run a leak check and store the
# results in log.txt
val:
	valgrind --leak-check=full --tool=memcheck ./pseudo-shell > log.txt 2>&1