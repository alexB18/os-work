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
/*---------------------------------------------------------------------------*/

/*-----------------------------Program Main----------------------------------*/
int main(int argc, char* argv[]) {
	setbuf(stdout, NULL);

	/* Main Function Variables */
	int CONTINUE = 1;
	int i;
	char *inBufferPtr, *token, **savePtr;
	size_t bufferSize = 60;


	/* Allocate memory for the input inBufferPtr. and savePtr */
	inBufferPtr = (char*) malloc(bufferSize * sizeof(char));
	savePtr = (char**) malloc(sizeof(char*));

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

			}else if(strcmp(token, "\n") == 0){
				break;

			}else{
				fprintf(stdout, "T%i: %s\n", i, token);
				i++;
			}
		}
	}
	/*Free the allocated memory*/
	free(inBufferPtr);
	free(savePtr);
	exit(EXIT_SUCCESS);
}
/*-----------------------------Program End-----------------------------------*/
