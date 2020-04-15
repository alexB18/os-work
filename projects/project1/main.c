/*
* Description: String processing in C. 
* 		1. Takes input from the console using "getline()".
* 		2. Tokenizes the input string and displays each individual
* 		   token on stdout.
*
* Author: Alex Brown
*
* Date: 4/7/2020
*
* Notes:
* 1. <add notes we should consider when grading>
*/

/*-------------------------Preprocessor Directives---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
/*---------------------------------------------------------------------------*/

// 0 -> interactive mode
// 1 -> file mode
int MODE;  


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

	if(strcmp(command, "ls") == 0){
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

/*-----------------------------Program Main----------------------------------*/
int main(int argc, char* argv[]) {
	setbuf(stdout, NULL);

	// check usage and set appropriate mode
	MODE = usage(argc, argv);
	fprintf(stdout, "Mode: %i\n", MODE);

	/* Main Function Variables */
	int CONTINUE = 1;
	int i;
	char *inBufferPtr, *token, **savePtr;
	size_t bufferSize = 60;


	/* Allocate memory for the input inBufferPtr. and savePtr */
	inBufferPtr = (char*) malloc(bufferSize * sizeof(char));
	savePtr = (char**) malloc(sizeof(char*));

	/* If in "interactive" mode, ask user for input and respond 
	in kind */
	if (MODE == 0){

		/*main run loop*/
		while (CONTINUE){

			/* Print >>> then get the input string */
			fprintf(stdout, ">>> ");
			getline(&inBufferPtr, &bufferSize, stdin);
			inBufferPtr[strlen(inBufferPtr) - 1] = 0;
			*savePtr = inBufferPtr;

			if(strlen(inBufferPtr) > 0){
				fprintf(stdout, "\n");	
			}

			/* Tokenize the input string */
			/* Display each token */
			i = 0;
			while ((token = strtok_r(*savePtr, " ", savePtr))){

				// If the user entered <exit> then exit both loops
				if(strcmp(token, "exit") == 0){
					CONTINUE = 0;
					break;

				// If the user entered nothing, then simply repeat loop
				}else if(strcmp(token, "\n") == 0){
					break;

				}
				else {
					execUnixCmd(token);
				}

				// DEBUG: Tokenize input and print
				/*
				}else{
					fprintf(stdout, "T%i: %s\n", i, token);
					i++;
				}*/
			}
		}

	
	/* If in "file" mode, read commands from input file */
	} else if(MODE == 1){

		// Init input and output file names
		char* inFileName = argv[2];
		char* outFileName = "output.txt";

		// Attempt to open input file
		FILE* inFilePointer = fopen(inFileName, "r");

		// Check if input file exists, exit otherwise
		if(inFilePointer == NULL){
			fprintf(stderr, "fopen() failed to open file %s", inFileName);
			exit(EXIT_FAILURE);
		}

		// open output file and create one if it doesn't exist
		FILE* outFilePointer = fopen(outFileName, "w+");

		// Get input from input file line by line until ther are no more lines
		while(getline(&inBufferPtr, &bufferSize, inFilePointer) != -1){

			//Strip null character from end of buffer and save current Buffer
			inBufferPtr[strlen(inBufferPtr) - 1] = 0;
			*savePtr = inBufferPtr;

			// Check if current buffer is empty
			if(strlen(inBufferPtr) > 0){
				fprintf(outFilePointer, "\n");
			}

			/* Tokenize the input string */
			/* Display each token */
			i = 0;
			while ((token = strtok_r(*savePtr, " ", savePtr))){

				// If the user entered exit, exit both loops
				if(strcmp(token, "exit") == 0){
					break;
				
				} else if(strcmp(token, "\n") == 0){
					break;
				
				} else {
					fprintf(outFilePointer, "T%i: %s\n", i, token);
					i++;
				}
				

			}

		}

		// Close file pointers
		fclose(inFilePointer);
		fclose(outFilePointer);

	}
	/*Free the allocated memory*/
	free(inBufferPtr);
	free(savePtr);
	exit(EXIT_SUCCESS);
}
/*-----------------------------Program End-----------------------------------*/
