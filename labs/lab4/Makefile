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
CFLAGS =  -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: lab4 iobound

# To create the executable file count we need the object file
# main.o
#
lab4: main.o
	$(CC) $(CFLAGS) -o a.out main.o

iobound: iobound.o
	$(CC) $(CFLAGS) -o iobound iobound.o


# To create the object file main.o, we need the source file
# main.c
#
main.o: main.c 
	$(CC) $(CFLAGS) -c main.c

iobound.o: iobound.c
	$(CC) $(CFLAGS) -c iobound.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) a.out iobound log.txt *.o *~

# To run valgrind in interactive mode, type 'make val-interactive'
# To run valgrind in file mode, type 'make val-file'
# Valgrind will run a leak check and store the
# results in log.txt
val: lab4 iobound
	valgrind --leak-check=full --tool=memcheck ./a.out 5 > log.txt 2>&1

