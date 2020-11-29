
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
default: server queue_test queue_test_advanced entry_test

# To create the executable file count we need the object file(s)
# part1.o:
#
server:  Entry.o TopicQueue.o main.o
	$(CC) $(CFLAGS) -pthread -o server Entry.o TopicQueue.o main.o

# Rule for testing just the Entry object
entry_test: Entry.o entry_test.o
	$(CC) $(CFLAGS) -o entry_test Entry.o entry_test.o

queue_test: TopicQueue.o Entry.o queue_test.o
	$(CC) $(CFLAGS) -pthread -o queue_test TopicQueue.o Entry.o queue_test.o

queue_test_advanced: TopicQueue.o Entry.o queue_test_advanced.o
	$(CC) $(CFLAGS) -pthread -o queue_test_advanced TopicQueue.o Entry.o queue_test.o



# To create the object file entries.o, we need the source
# file(s) entries.c and the header file entries.h:
#
Entry.o: Entry.c
	$(CC) $(CFLAGS) -c Entry.c

TopicQueue.o: TopicQueue.c
	$(CC) $(CFLAGS) -c TopicQueue.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

entry_test.o: entry_test.c
	$(CC) $(CFLAGS) -c entry_test.c

queue_test.o: queue_test.c
	$(CC) $(CFLAGS) -c queue_test.c

queue_test_advanced.o: queue_test_advanced.c
	$(CC) $(CFLAGS) -c queue_test_advanced.c

clean: 
	$(RM) server queue_test queue_test_advanced log.txt output.txt *.o *~ *_test

# To run valgrind, type 'make val-file'
# Valgrind will run a leak check and store the
# results in log.txt
val: server
	valgrind -v --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./server > log.txt 2>&1

val_entry_test: entry_test
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./entry_test > log.txt 2>&1

val_queue_test: queue_test
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./queue_test > log.txt 2>&1

val_queue_test_advanced: queue_test_advanced
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes ./queue_test_advanced > log.txt 2>&1



