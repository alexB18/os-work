/*
* Description: 
*	
*	--String Processing in C using file I/0--
*
* 		1. Take input from .txt file containing a list of bash commands
* 		   (or any string really)
* 		2. Tokenize each line from the input file and write each
* 		   individual token to an output .txt file
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
/*---------------------------------------------------------------------------*/

/*-----------------------------Program Main----------------------------------*/
void main(int argc, char* argv[]) {
	setbuf(stdout, NULL);

	/* Main Function Variables */
	int CONTINUE = 1;
	int i;
	char *inBufferPtr, *token, **savePtr;
	size_t bufferSize = 60;
	size_t numCharacters;


	/* Allocate memory for the input inBufferPtr. and savePtr */
	inBufferPtr = (char*) malloc(bufferSize * sizeof(char));
	savePtr = (char**) malloc(sizeof(char*));

	// Init input and output file names
	char* inFileName = argv[1];
	char* outFileName = argv[2];

	// Attempt to open input file
	FILE* inFilePointer = fopen(inFileName, "r");

	// Check if input file exists, exit otherwise
	if(inFilePointer == NULL){
		fprintf(stderr, "fopen() failed to open file %s", inFileName);
		exit(EXIT_FAILURE);
	}

	// Attempt to open output file
	FILE* outFilePointer = fopen(outFileName, "w");

	// Check if output file exists, exit otherwise
	if(outFilePointer == NULL){
		fprintf(stderr, "fopen() failed to open file %s", outFileName);
		exit(EXIT_FAILURE);
	}

	// get input from input file line by line until there are no more lines
	while(getline(&inBufferPtr, &bufferSize, inFilePointer) != -1){

		// Strip null character from end of buffer and save current Buffer to savePtr
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

			// If the user entered <exit> then exit both loops
			if(strcmp(token, "exit") == 0){
				break;

			}else if(strcmp(token, "\n") == 0){
				break;

			}else{
				fprintf(outFilePointer, "T%i: %s\n", i, token);
				i++;
			}
		}

	}


	// Close file pointers
	fclose(inFilePointer);
	fclose(outFilePointer);

	/*Free the allocated memory*/
	free(inBufferPtr);
	free(savePtr);
	exit(EXIT_SUCCESS);
}
/*-----------------------------Program End-----------------------------------*/
