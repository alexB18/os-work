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
#include <sys/types.h>
#include <sys/wait.h>
/*---------------------------------------------------------------------------*/

int main(int argc, char** argv){

    /* Main Function Variables */
    int numLineCharacters, i, j, k;
    char *currentLinePtr, *inFileName, *cmdPtr, *arg, **lineSavePtr, **cmdSavePtr, **args;
    // size of current *line* buffer
    size_t lineBufferSize = 512;
    // size of current *command separated by ; * buffer
    size_t cmdBufferSize = 256;
    // size of *argument in current command* buffer
    size_t argBufferSize = 128;
    // size of arrray holding args for current command
    size_t argsBufferSize = 10;
    // int describing process idS
    pid_t pid;

    /* Allocate memory for the input inBufferPtr and savePtr */
    currentLinePtr = (char*) malloc(lineBufferSize * sizeof(char));
    lineSavePtr = (char**) malloc(lineBufferSize * sizeof(char*));
    cmdSavePtr = (char**) malloc(cmdBufferSize * sizeof(char*));
    args = (char**) malloc(argsBufferSize * sizeof(char*));

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

    /* ----------------------------------------------------------- */
    /* 1. Read the program workload from the specified input file. */
    /* ----------------------------------------------------------- */
    
    // Main run cycle
    i = 0;
    do
    {
        // Get input from input file line by line until there are no more lines
        numLineCharacters = getline(&currentLinePtr, &lineBufferSize, stdin);

        // Strip newline at the end of the input string
        currentLinePtr[strlen(currentLinePtr) - 1] = '\0';

        // save copy of currentLinePtr
        *lineSavePtr = currentLinePtr;

        /* Tokenize each line by semicolon */
        j = 0;
        while((cmdPtr = strtok_r(*lineSavePtr, ";", lineSavePtr))){

            // Next, save copy of current command
            *cmdSavePtr = cmdPtr;

            // Tokenize each command by space
            k = 0;
            while((arg = strtok_r(*cmdSavePtr, " ", cmdSavePtr)) && (numLineCharacters != -1)){

                if(strcmp(arg, "\n") == 0){
                    i++;
                }

                // DEBUG: print each token
                fprintf(stdout, "Line[%i], Command[%i], Arg[%i]: %s\n", i, j, k, arg);
                
                // Add arg to collection of args
                args[k] = arg;
                k++;
            }
            j++;
        }
        // DEBUG: print newline after above DEBUG statement has finished
        fprintf(stdout, "\n");
        i++;
    }while (numLineCharacters != -1);

    // Now that the input has been tokenized, we can start launching processes

    // Free allocated memory
    free(currentLinePtr);
    free(lineSavePtr);
    free(cmdSavePtr);
    free(args);

    /* 2. For each program, MCP mush launch program to run as separate process
    using some variant of fork(2) and one of the exec() system calls. */

    /* 3. Once all of the programs are running, MCP must wait for each program to
    terminate using the system call wait(). */

    /* 4. After all programs have terminated, MCP must exit using the exit() 
    system call. */

}