
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
default: mcp1 mcp2 mcp3 mcp4 iobound cpubound

# To create the executable file count we need the object file(s)
# part1.o:
#
mcp1:  mcp1.o
	$(CC) $(CFLAGS) -o mcp1 mcp1.o

mcp2:  mcp2.o
	$(CC) $(CFLAGS) -o mcp2 mcp2.o

mcp3:  mcp3.o
	$(CC) $(CFLAGS) -o mcp3 mcp3.o

mcp4:  mcp4.o
	$(CC) $(CFLAGS) -o mcp4 mcp4.o

iobound: iobound.o
	$(CC) $(CFLAGS) -o iobound iobound.o

cpubound: cpubound.o
	$(CC) $(CFLAGS) -o cpubound cpubound.o

# To create the object file part1.o, we need the source
# file(s) part1.c:
#
mcp1.o:	mcp1.c
	$(CC) $(CFLAGS) -c mcp1.c

mcp2.o: mcp2.c
	$(CC) $(CFLAGS) -c mcp2.c

mcp3.o: mcp3.c
	$(CC) $(CFLAGS) -c mcp3.c

mcp4.o: mcp4.c
	$(CC) $(CFLAGS) -c mcp4.c

iobound.o: iobound.c
	$(CC) $(CFLAGS) -c iobound.c

cpubound.o: cpubound.c
	$(CC) $(CFLAGS) -c cpubound.c

clean: 
	$(RM) mcp1 mcp2 mcp3 mcp4 cpubound iobound log.txt *.o *~

# To run valgrind, type 'make val-file'
# Valgrind will run a leak check and store the
# results in log.txt
val-part1: mcp1
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./mcp1 input.txt > log1.txt 2>&1

val-part2: mcp2
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./mcp2 input.txt > log2.txt 2>&1

val-part3: mcp3
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./mcp3 input.txt > log3.txt 2>&1

val-part4: mcp4
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./mcp4 input.txt > log4.txt 2>&1


