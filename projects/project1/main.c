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
	if(argc == 1){
		return 0;
	}

	// else if pseudo-shell is being run with two arguments, we could be in file mode,
	// and must further validate
    else if(argc == 3){

		// so, we need to make sure that the correct arguments are included
		// we also need to check that there are no more than 2 parameters

		if(strcmp(argv[1], "-f") == 0){
			return 1;

		} else {
			fprintf(stderr, 
                "usage: %s <input file 1> <input file 2> <output file>\n", 
                argv[0]);
        	exit(EXIT_FAILURE);
		}

    
	// else, the usage is incorrect
	} else {

		fprintf(stderr, 
                "usage: %s <input file 1> <input file 2> <output file>\n", 
                argv[0]);
        exit(EXIT_FAILURE);

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
