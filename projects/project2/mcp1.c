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
    int numLineCharacters, lineCounter, commandCounter, argCounter, numPrograms, i;
    char *currentLinePtr, *inFileName, *cmdPtr, *arg, **lineSavePtr, **cmdSavePtr, **args, ***programs;
    // size of current *line* buffer
    size_t lineBufferSize = 512;
    // size of current *command separated by ; * buffer
    size_t cmdBufferSize = 256;
    // size of *argument in current command* buffer
    size_t argBufferSize = 128;
    // size of arrray holding args for current command
    size_t argsBufferSize = 10;
    // size of array holding all programs
    size_t programsBufferSize = 50;
    // int describing process idS
    pid_t* pid;

    /* Allocate memory for the input inBufferPtr and savePtr */
    currentLinePtr = (char*) malloc(lineBufferSize * sizeof(char));
    lineSavePtr = (char**) malloc(lineBufferSize * sizeof(char*));
    cmdSavePtr = (char**) malloc(cmdBufferSize * sizeof(char*));
    args = (char**) malloc(argsBufferSize * sizeof(char*));
    programs = (char***) malloc(programsBufferSize *sizeof(char**));

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
    numPrograms = 0;
    lineCounter = 0;
    do
    {
        // Get input from input file line by line until there are no more lines
        numLineCharacters = getline(&currentLinePtr, &lineBufferSize, stdin);

        // Strip newline at the end of the input string
        currentLinePtr[strlen(currentLinePtr) - 1] = '\0';

        // save copy of currentLinePtr
        *lineSavePtr = currentLinePtr;

        /* Tokenize each line by semicolon */
        commandCounter = 0;
        while((cmdPtr = strtok_r(*lineSavePtr, ";", lineSavePtr))){

            // Next, save copy of current command
            *cmdSavePtr = cmdPtr;

            // Tokenize each command by space
            argCounter = 0;
            while((arg = strtok_r(*cmdSavePtr, " ", cmdSavePtr)) && (numLineCharacters != -1)){

                if(strcmp(arg, "\n") == 0){
                    lineCounter++;
                }

                // DEBUG: print each token
                //fprintf(stdout, "Line[%i], Command[%i], Arg[%i]: %s\n", lineCounter, commandCounter, argCounter, arg);
                
                // Add arg to collection of args
                args[argCounter] = arg;

                argCounter++;
            }

            // Save current command to programs array
            programs[numPrograms]= args;

            // DEBUG: Print current program with arguments
            
            /*
            fprintf(stdout, "program[%i]\n", numPrograms);
            for(int i = 0; i < argCounter ; i++){
                fprintf(stdout, "arg[%i] %s\n", i, programs[numPrograms][i]);
            }
            fprintf(stdout, "\n");
            */
            


            // increment global numPrograms and local commandCounter
            numPrograms ++;
            commandCounter++;
        }
        lineCounter++;
    }while (numLineCharacters != -1);

    
    //fprintf(stdout, "Line[%i], Command[%i], Arg[%i]: %s\n", lineCounter, commandCounter, argCounter, arg);

    // Now that we've gathered all programs, it's time to start forking things up
    //Allocate the required memory for pid array
    pid = (pid_t*) malloc(numPrograms * sizeof(pid_t));


    for(i = 0; i < numPrograms; i++){

        pid[i] = fork();

        //fprintf(stdout, "Current pid:[%i]\n",  pid[i]);

        // Check for error
        if(pid[i] < 0){
            fprintf(stderr, "ERROR! Unable to fork.\n");
            // Free allocated memory
            free(currentLinePtr);
            free(lineSavePtr);
            free(cmdSavePtr);
            free(args);
            free(programs);
            exit(EXIT_FAILURE); 
        }

        // Case where process is parent
        if(pid[i] == 0){
            execvp(programs[i][0], programs[i]);
            exit(-1);
        }
    }

    for(i = 0; i < numPrograms; i++){
        wait(pid[i]);
    }

    // Free allocated memory
    free(currentLinePtr);
    free(lineSavePtr);
    free(cmdSavePtr);
    free(args);
    free(programs);




    /* 2. For each program, MCP mush launch program to run as separate process
    using some variant of fork(2) and one of the exec() system calls. */

    /* 3. Once all of the programs are running, MCP must wait for each program to
    terminate using the system call wait(). */

    /* 4. After all programs have terminated, MCP must exit using the exit() 
    system call. */

}