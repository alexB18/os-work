/*
* Description:
*
* Author: Alex Brown
*
* Date: 4/28/2020
*
* Notes:
*/

/*-------------------------Preprocessor Directives---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
/*---------------------------------------------------------------------------*/

int main(int argc, char** argv){

    /* Main Function Variables */
    int numLineCharacters, i, j;
    char *currentLinePtr, *inFileName, *cmdPtr, *arg, **lineSavePtr, **cmdSavePtr;
    size_t lineBufferSize = 512;
    size_t cmdBufferSize = 256;
    size_t argBufferSize = 128;

    /* Allocate memory for the input inBufferPtr and savePtr */
    currentLinePtr = (char*) malloc(lineBufferSize * sizeof(char));
    lineSavePtr = (char**) malloc(lineBufferSize * sizeof(char*));
    cmdSavePtr = (char**) malloc(cmdBufferSize * sizeof(char*));

    /* Init. inFilePtr to null by default */
    FILE *inFilePtr;

    // Retrieve input file name
    inFileName = argv[1];

    // Attempt to open input file and switch context of stdin
    inFilePtr = freopen(inFileName, "r", stdin);

    // Check if input file exists, exit otherwise
    if(inFilePtr == NULL){
		fprintf(stderr, "freopen() failed to open file %s\n", inFileName);
        free(currentLinePtr);
        free(lineSavePtr);
        exit(EXIT_FAILURE);
    }

    // Main run cycle
    do
    {
        // Get input from input file line by line until there are no more lines
        numLineCharacters = getline(&currentLinePtr, &lineBufferSize, stdin);

        // save copy of currentLinePtr
        *lineSavePtr = currentLinePtr;

        /* Tokenize each line by semicolon */
        i = 0;
        while((cmdPtr = strtok_r(*lineSavePtr, ";", lineSavePtr))){

            // Next, save copy of current command
            *cmdSavePtr = cmdPtr;

            // Tokenize each command by space
            j = 0;
            while((arg = strtok_r(*cmdSavePtr, " ", cmdSavePtr))){

                // DEBUG: print each token
                fprintf(stdout, "Command[%i], Arg[%i]: %s\n", i, j, arg);
                j++;
            }

            i++;
        }
    }while (numLineCharacters != -1);
    //

    /* 1. Read the program workload from the specified input file. */

    /* 2. For each program, MCP mush launch program to run as separate process
    using some variant of fork(2) and one of the exec() system calls. */

    /* 3. Once all of the programs are running, MCP must wait for each program to
    terminate using the system call wait(). */

    /* 4. After all programs have terminated, MCP must exit using the exit() 
    system call. */

}