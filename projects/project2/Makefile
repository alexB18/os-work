
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
default: part1 part2 part3

# To create the executable file count we need the object file(s)
# part1.o:
#
part1:  part1.o
	$(CC) $(CFLAGS) -o part1 part1.o

part2:  part2.o
	$(CC) $(CFLAGS) -o part2 part2.o

part3:  part3.o
	$(CC) $(CFLAGS) -o part3 part3.o

iobound: iobound.o
	$(CC) $(CFLAGS) -o iobound iobound.o

cpubound: cpubound.o
	$(CC) $(CFLAGS) -o cpubound cpubound.o

# To create the object file part1.o, we need the source
# file(s) part1.c:
#
part1.o:	part1.c
	$(CC) $(CFLAGS) -c part1.c

part2.o: part2.c
	$(CC) $(CFLAGS) -c part2.c

part3.o: part3.c
	$(CC) $(CFLAGS) -c part3.c

iobound.o: iobound.c
	$(CC) $(CFLAGS) -c iobound.c

cpubound.o: cpubound.c
	$(CC) $(CFLAGS) -c cpubound.c

clean: 
	$(RM) part1 part2 part3 cpubound iobound log.txt *.o *~

# To run valgrind, type 'make val-file'
# Valgrind will run a leak check and store the
# results in log.txt
val-part1: part1
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./part1 input.txt > log.txt 2>&1

val-part2: part2
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./part2 input.txt > log.txt 2>&1

val-part3: part3
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./part3 input.txt > log.txt 2>&1


