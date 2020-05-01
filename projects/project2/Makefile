
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
default: mcp1

# To create the executable file count we need the object file(s)
# mcp1.o:
#
mcp1:  mcp1.o
	$(CC) $(CFLAGS) -o mcp1 mcp1.o

# To create the object file mcp1.o, we need the source
# file(s) mcp1.c:
#
mcp1.o:  mcp1.c
	$(CC) $(CFLAGS) -c mcp1.c

clean: 
	$(RM) mcp1 log.txt *.o *~

# To run valgrind, type 'make val-file'
# Valgrind will run a leak check and store the
# results in log.txt
val-file: mcp1
	valgrind --leak-check=full --tool=memcheck ./mcp1 -f input.txt > log.txt 2>&1
