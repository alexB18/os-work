/*
* Description: <write a brief description of your lab>
*
* Author: <your name>
*
* Date: <today's date>
*
* Notes:
* 1. <add notes we should consider when grading>
*/

/*-------------------------Preprocessor Directives---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "command.h"
/*---------------------------------------------------------------------------*/

// 0 -> interactive mode
// 1 -> file mode
int MODE;

/*--------------------------- Helper Functions ------------------------------*/

/* This function checks the input parameters to the program to make 
   sure they are correct. If the number of input parameters is incorrect, or 
   if inproper parameters are used, it prints out a message on how to properly use the program.

   returns an int corresponding to the running mode of ./pseudo-shell
   0 --> interactive mode
   1 --> file mode

   input parameters:
       int    argc
       char** argv 
    return parameters:
       int
 */
int usage(int argc, char** argv)
{
	
	// if pseudo-shell is being run with *exactly* one argument (./pseudo-shell),
	// then we're in "interactive mode"
	if(argc == 1){return 0;}

	// else if pseudo-shell is being run with two arguments, we could be in file mode,
	// and must further validate
    else if(argc == 3){

		// so, we need to make sure that the correct arguments are included
		// we also need to check that there are no more than 2 parameters

		if(strcmp(argv[1], "-f") == 0){
			return 1;

		} else {
			fprintf(stderr, 
                "usage: %s <flag> <input file>\n", 
                argv[0]);
        	exit(EXIT_FAILURE);
		}

    
	// else, the usage is incorrect
	} else {

		fprintf(stderr, 
                "usage: %s <flag> <input file>\n", 
                argv[0]);
        exit(EXIT_FAILURE);

	}
}

void execUnixCmd(char* command){
	if(strcmp(command, "lfcat") == 0){
		fprintf(stdout, "%s not yet implemented in command.c\n", command);

	} else if(strcmp(command, "ls") == 0){
		fprintf(stdout, "%s not yet implemented in command.c\n", command);
	
	} else if(strcmp(command, "pwd") == 0){
		fprintf(stdout, "%s not yet implemented in command.c\n", command);
	
	} else if(strcmp(command, "mkdir") == 0){
		fprintf(stdout, "%s not yet implemented in command.c\n", command);
	
	} else if(strcmp(command, "cd") == 0){
		fprintf(stdout, "%s not yet implemented in command.c\n", command);
	
	} else if(strcmp(command, "cp") == 0){
		fprintf(stdout, "%s not yet implemented in command.c\n", command);
	
	} else if(strcmp(command, "mv") == 0){
		fprintf(stdout, "%s not yet implemented in command.c\n", command);
	
	} else if(strcmp(command, "rm") == 0){
		fprintf(stdout, "%s not yet implemented in command.c\n", command);

	} else if(strcmp(command, "cat") == 0){
		fprintf(stdout, "%s not yet implemented in command.c\n", command);

	} else {
		fprintf(stdout, "Unrecognized command.\n");
	}
}
/*---------------------------------------------------------------------------*/

/*-----------------------------Program Main----------------------------------*/
int main(int argc, char** argv) {
	setbuf(stdout, NULL);

	// Global Variable Initializations
	MODE = usage(argc, argv);
	/* DEBUG
	fprintf(stdout, "Mode: %i\n", MODE);
	*/

	/* Main Function Variables */
	int CONTINUE = 1;
	int numLineCharacters;
	char *inBufferPtr, *token, **savePtr;
	size_t bufferSize = 80;

	/* Allocate memory for the input inBufferPtr. and savePtr */
	inBufferPtr = (char*) malloc(bufferSize * sizeof(char));
	savePtr = (char**) malloc(sizeof(char*));

	/* Initialize inFilePointer and outFilePointer to null by default */
	FILE *inFilePointer, *outFilePointer;	

	/* Switch the context of STDOUT if the program is started with the -f flag.
	   Open the file for reading and open a file "output.txt" for writing.
	   Hint: use freopen() to switch the context of a file descriptor. */
	if(MODE == 1){

		//Init input and output file names
		char* inFileName = argv[2];
		char* outFileName = "output.txt";

		//FILE* freopen(const char* pathname, const char* mode, FILE* stream);
		// Attempt to create/open output file and switch context of stdout
		outFilePointer = freopen(outFileName, "w+", stdout);

		// Check if outFilePointer was created succesfully
		if(outFilePointer == NULL){
			fprintf(stderr, "freopen() failed to create/open file %s\n", outFileName);
			exit(EXIT_FAILURE);
		}

		// Attempt to open input file and switch context of stdin
		inFilePointer = freopen(inFileName, "r", stdin);

		// Check if input file exists, exit otherwise
		if(inFilePointer == NULL){
			fprintf(stderr, "freopen() failed to open file %s\n", inFileName);
			exit(EXIT_FAILURE);
		}

	}
	
		 // Remove the newline at the end of the input string.
	 	//Hint: use strcspn(2) to find where the newline is then assign '\0' there.

	// Main run cycle
	do
	{
		// Display prompt and read input from console/file using getline(3)
		// Get input from input file line by line until ther are no more lines
		fprintf(stdout, ">>> ");
		numLineCharacters = getline(&inBufferPtr, &bufferSize, stdin);


		// Strip newline at the end of the input string
		inBufferPtr[strlen(inBufferPtr) - 1] = 0;

		// Save copy of inBufferPointer
		*savePtr = inBufferPtr;

		if(strlen(inBufferPtr) > 0){
			fprintf(stdout, "\n");
		}		
	
		/* Tokenize and process the input string. Remember there can be multiple
		calls to lfcat. i.e. lfcat ; lfcat <-- valid
			If the command is either 'exit' or 'lfcat' then do the approp. things.
		Note: you do not need to explicitly use an if-else clause here. For
				instance, you could use a string-int map and a switch statement
					or use a function that compares the input token to an array of
					commands, etc. But anything that gets the job done gets full points so
					think creatively. ^.^  Don't forget to display the error messages
					seen in the lab discription*/
		while ((token = strtok_r(*savePtr, " ", savePtr))){
			
			// If the user entered <exit> then exit both loops
			if(strcmp(token, "exit") == 0){
					CONTINUE = 0;
					break;	
			
			// If the user entered nothing, then simply repeat loop & ask for input again
			} else if(strcmp(token, "\n") == 0){
				break;
			
			} else{
				execUnixCmd(token);
			}		
		}

	} while((numLineCharacters != -1) && (CONTINUE));

	/*Free the allocated memory and close any open files*/
	
	if(MODE == 1){
		fclose(inFilePointer);
		fclose(outFilePointer);
	}

	free(inBufferPtr);
	free(savePtr);

	return 0;
}
/*-----------------------------Program End-----------------------------------*/