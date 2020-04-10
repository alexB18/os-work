/*
* Description: <write a brief description of your lab>
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
	char *inBufferPtr, *token, **savePtr;
	size_t bufferSize = 60;
	size_t numCharacters;

	
	/* Allocate memory for the input inBufferPtr. and savePtr */
	//inBufferPtr = (char*) malloc(bufferSize * sizeof(char));
	token = (char*) malloc(bufferSize * sizeof(char));

	savePtr = (char**) malloc(sizeof(char*));
	//savePtr = (char*) malloc(bufferSize * sizeof(char));
    //token = (char* ) malloc(bufferSize * sizeof(char));

	if (inBufferPtr == NULL){
		fprintf(stderr, "Unable to allocate inBufferPtr");
		free(inBufferPtr);
		free(token);
		free(savePtr);
		exit(EXIT_FAILURE);
	}
	
	/*main run loop*/
	while (CONTINUE){

		/* Print >>> then get the input string */
		fprintf(stdout, ">>> ");
		getline(&inBufferPtr, &bufferSize, stdin);
		//fprintf(stdout, "%s", inBufferPtr);


		//DEBUG
		//fprintf(stdout, "You typed: %s", inBufferPtr);

		/* Tokenize the input string */
		/* Display each token */
		
		
		*savePtr = inBufferPtr;
        //token = strtok_r(savePtr, " ", &savePtr);
		while ((token = strtok_r(*savePtr, " ", savePtr))){
            fprintf(stdout, "%s\n", token);
		
		// If the user entered <exit> then exit the loop
			if(strcmp(token, "exit\n") == 0){
				CONTINUE = 0;
				break;
			}
		}
	}
	/*Free the allocated memory*/
	free(inBufferPtr);
	free(savePtr);
    free(token);
	exit(EXIT_SUCCESS);
}
/*-----------------------------Program End-----------------------------------*/
