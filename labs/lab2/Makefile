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
default: lab2

# To create the executable file count we need the object file
# main.o
#
lab2-interactivemode: main.o
	$(CC) $(CFLAGS) -o lab2-interactivemode main.o

lab2-filemode: main2.o
	$(CC) $(CFLAGS) -o lab2-filemode main2.o

# To create the object file main.o, we need the source file
# main.c
#
main.o:  main.c 
	$(CC) $(CFLAGS) -c main.c

main2.o:  main2.c 
	$(CC) $(CFLAGS) -c main2.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) lab2-filemode lab2-interactivemode output.txt log.txt *.o *~

# To run valgrind in interactive mode, type 'make val-interactive'
# To run valgrind in file mode, type 'make val-file'
# Valgrind will run a leak check and store the
# results in log.txt
val-interactivemode: lab2-interactivemode
	valgrind --leak-check=full --tool=memcheck ./lab2-interactivemode > log.txt 2>&1

val-filemode: lab2-filemode
	valgrind --leak-check=full --tool=memcheck ./lab2-filemode input.txt > log.txt 2>&1
