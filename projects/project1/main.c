/*
* Description: Implement a "pseudo-shell" which can perform the
*				following UNIX commands without flags:
*				ls, pwd, mkdir, cd, cp, mv, rm, cat
*
* Author: Alex Brown
*
* Date: 4/19/2020
*
* Notes:
* 1. I worked closely with Stephanie Schofield toward the 
*	end of this project. We worked a bit together to make her 
*	initial do-while loop asking for user input, talked 
*	extensively on how best to tokenize and process input, 
*	and utilized similar helper functions
*
* 2. I ran into a strange set of errors in valgrind when 
*  	executing the cat command. When running valgrind (and 
*	during compilation) I am warned of using an uninitialized 
*	value in my displayFile function in command.c . 
*	However, for the life of me, I was unable to implement 
*	the function in any other way without getting 
*	unexpected/incorrect results. The project specification 
*	stated that no *memory leaks* were allowed, so for the 
*	sake of time I let it be.
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
// Pointer which will hold an array of all valid commands
char** VALID_COMMANDS;
int NUM_OF_COMMANDS = 8;

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

/* This function checks whether a given string is a valid UNIX
	command within the scope of the project. 

   returns an int corresponding to whether or not the entered
   string is avalid UNIX command
   0 --> invalid
   1 --> valid

   input parameters:
       char* command
    return parameters:
       int
 */
int isValidCommand(char* command){

	int result = 0;

	//compare command with every command in VALID_COMMANDS
	for(int i = 0; i < NUM_OF_COMMANDS; i++){
		
		// If we have any kind of match, set result to 1 and break
		if(strcmp(VALID_COMMANDS[i], command) == 0){
			result = 1;
			break;
		}
	}

	return result;
}

/* calls the necessary function in command.c associated with the linux comand
	the user entered

   returns nothing

   input parameters:
       char** command
       int args 
    return parameters:
       void
 */
void execUnixCmd(char** command, int args){

	// If args == 0, then the user likely entered "exit"
	if(args == 0){
		return;
		
	} else if(strcmp(command[0], "ls") == 0){
		//fprintf(stdout, "%s not yet implemented in command.c\n", command);
		if(args != 1){
			fprintf(stderr, "Error! Unsupported parameters for command: %s\n", command[0]);
		} else {
			listDir();
		}
		
	} else if(strcmp(command[0], "pwd") == 0){
		//fprintf(stdout, "%s not yet implemented in command.c\n", command);
		if(args != 1){
			fprintf(stderr, "Error! Unsupported parameters for command: %s\n", command[0]);
		} else {
			showCurrentDir();
		}
	
	} else if(strcmp(command[0], "mkdir") == 0){
		if(args != 2){
			fprintf(stderr, "Error! Unsupported parameters for command: %s\n", command[0]);
		} else {
			//fprintf(stdout, "%s not yet implemented in command.c\n", command[0]);
			makeDir(command[1]);
		}

	} else if(strcmp(command[0], "cd") == 0){
		if(args != 2){
			fprintf(stderr, "Error! Unsupported parameters for command: %s\n", command[0]);
		} else {
			//fprintf(stdout, "%s not yet implemented in command.c\n", command[0]);
			changeDir(command[1]);
		}
	
	} else if(strcmp(command[0], "cp") == 0){
		if(args != 3){
			fprintf(stderr, "Error! Unsupported parameters for command: %s\n", command[0]);
		} else {
			//fprintf(stdout, "%s not yet implemented in command.c\n", command[0]);
			copyFile(command[1], command[2]);
		}
	
	} else if(strcmp(command[0], "mv") == 0){
		if(args != 3){
			fprintf(stderr, "Error! Unsupported parameters for command: %s\n", command[0]);
		} else {
			//fprintf(stdout, "%s not yet implemented in command.c\n", command[0]);
			moveFile(command[1], command[2]);
		}
	
	} else if(strcmp(command[0], "rm") == 0){
		if(args != 2){
			fprintf(stderr, "Error! Unsupported parameters for command: %s\n", command[0]);
		} else {
			//fprintf(stdout, "%s not yet implemented in command.c\n", command[0]);
			deleteFile(command[1]);
		}

	} else if(strcmp(command[0], "cat") == 0){
		if(args != 2){
			fprintf(stderr, "Error! Unsupported parameters for command: %s\n", command[0]);
		} else {
			//fprintf(stdout, "%s not yet implemented in command.c\n", command[0]);
			displayFile(command[1]);
		}

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


	VALID_COMMANDS = (char**) malloc(NUM_OF_COMMANDS * sizeof(char*));
	VALID_COMMANDS[0] = "ls";
	VALID_COMMANDS[1] = "pwd";
	VALID_COMMANDS[2] = "mkdir";
	VALID_COMMANDS[3] = "cd";
	VALID_COMMANDS[4] = "cp";
	VALID_COMMANDS[5] = "mv";
	VALID_COMMANDS[6] = "rm";
	VALID_COMMANDS[7] = "cat";

	/* Main Function Variables */
	int CONTINUE = 1;
	int TOKEN_ERROR, CONTROL_CODE;
	int numLineCharacters, i;
	char *inBufferPtr, *token, **savePtr, **tokens;
	size_t bufferSize = 80;
	size_t tokenBuffer = 3;

	/* Allocate memory for the input inBufferPtr, savePtr, and tokens */
	inBufferPtr = (char*) malloc(bufferSize * sizeof(char));
	savePtr = (char**) malloc(sizeof(char*));
	tokens = (char**) malloc(tokenBuffer * sizeof(char*));

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
			free(inBufferPtr);
			free(savePtr);
			free(tokens);
			free(VALID_COMMANDS);
			exit(EXIT_FAILURE);
		}

		// Attempt to open input file and switch context of stdin
		inFilePointer = freopen(inFileName, "r", stdin);

		// Check if input file exists, exit otherwise
		if(inFilePointer == NULL){
			fprintf(stderr, "freopen() failed to open file %s\n", inFileName);
			free(inBufferPtr);
			free(savePtr);
			free(tokens);
			fclose(outFilePointer);
			free(VALID_COMMANDS);
			exit(EXIT_FAILURE);
		}

	}

	// Main run cycle
	do
	{
		// Display prompt and read input from console/file using getline(3)
		// Get input from input file line by line until ther are no more lines
		fprintf(stdout, ">>> ");
		numLineCharacters = getline(&inBufferPtr, &bufferSize, stdin);


		// Strip newline at the end of the input string
		inBufferPtr[strlen(inBufferPtr) - 1] = '\0';

		// Save copy of inBufferPointer
		*savePtr = inBufferPtr;

		/*
		if(strlen(inBufferPtr) > 0){
			fprintf(stdout, "\n");
		}
		*/		
	
		/* Tokenize and process the input string. Remember there can be multiple
		calls to lfcat. i.e. lfcat ; lfcat <-- valid*/
		i = 0;
		while ((token = strtok_r(*savePtr, " ", savePtr))){
			// Set error flag and control code flag back to 0
			TOKEN_ERROR = 0;
			CONTROL_CODE = 0;

			
			// If the user entered <exit> then exit *both* loops
			if(strcmp(token, "exit") == 0){
					CONTINUE = 0;
					break;	

			/* If the token is control code, we need to check to make sure it isn't 
			at the end of the line*/
			} else if(strcmp(token, ";") == 0){

				//If tokens isn't empty, then we need to call execUnixCmd on it
				if( tokens != NULL){
					execUnixCmd(tokens, i);
				}

				/* Then we need to clear tokens for the next potential batch of parameters,
				reset i to 0, set CONTROL_CODE FLAG, and continue the tokenization loop*/
				free(tokens);
				tokens = (char**) malloc(tokenBuffer * sizeof(char*));
				i = 0;
				CONTROL_CODE = 1;
				continue;

			// If the current token is a valid command, we need to make sure it's the only one
			} else if(isValidCommand(token)){

				if(i > 0){
					fprintf(stderr, "Error! Incorrect syntax. No control code found.\n");
					TOKEN_ERROR = 1;
					break;
				}

				// If this command is the first valid one, add it to tokens
				tokens[i] = token;

			// Else the token might be a parameter and we need to make sure it's not the first argument 
			} else{
				
				if(i == 0){
					fprintf(stderr, "Error! Unrecognized command: %s \n\n", token);
					TOKEN_ERROR = 1;
					break;
				}

				tokens[i] = token;
			}

			i++;		
		}

		if( (!TOKEN_ERROR) ) {
			execUnixCmd(tokens, i);
		}

		/* If for some reason we've reached this point and CONTROL_CODE == 1
		then we've stumbled into the case where the last argument is ; and we
		need to print an error message*/
		if(CONTROL_CODE){
			fprintf(stderr, "Error! Unrecognized command: \n\n");
		}


	} while((numLineCharacters != -1) && (CONTINUE));

	/*Free the allocated memory and close any open files*/
	if(MODE == 1){
		fclose(inFilePointer);
		fclose(outFilePointer);
	}

	free(inBufferPtr);
	free(savePtr);
	free(tokens);
	free(VALID_COMMANDS);

	return 0;
}
/*-----------------------------Program End-----------------------------------*/