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

#define LINE_BUFFER_SIZE 512
#define PROGRAMS_BUFFER_SIZE 256
#define ARGS_BUFFER_SIZE 10
/*---------------------------------------------------------------------------*/

/*-----------------------------Helper Functions------------------------------*/
int countlines(char * filename){

    FILE* filePtr;
    char character;
    int numLines = 0;

    // Begin reading from file
    filePtr = fopen(filename, "r");
    // If there's an error, return -1
    if(filePtr == NULL){
        fprintf(stdout, "ERROR! File \"%s\" doesn't exist.\n", filename);
        return -1;
    }

    // Read file character by character to search for new lines
    while((character = fgetc(filePtr)) != EOF){
        if(character == '\n'){
            numLines++;
        }
    }

    // Close the file and return number of lines
    fclose(filePtr);
    return numLines;

}
/*---------------------------------------------------------------------------*/

int main(int argc, char** argv){

    /* Main Function Variables */
    int lineCounter, numArgs, numPrograms, status;
    char *currentLinePtr, *inFileName, *cmdPtr, **lineSavePtr, **args, ***programs;

    size_t programsBufferSizeHolder = PROGRAMS_BUFFER_SIZE;


    // DEBUG: Print number of detected lines (programs)
    numPrograms = countlines(argv[1]);
    if(numPrograms == -1 ){
        exit(EXIT_FAILURE);
    
    } else {
        fprintf(stdout, "Number of programs: %i\n", numPrograms);
    }

    // int describing process idS
    pid_t* pid = (pid_t*) malloc(numPrograms *sizeof(pid_t));

    /* Allocate memory for the input inBufferPtr and savePtr */
    currentLinePtr = (char*) malloc(LINE_BUFFER_SIZE * sizeof(char));
    lineSavePtr = (char**) malloc(LINE_BUFFER_SIZE * sizeof(char*));
    
    args = (char**) malloc(ARGS_BUFFER_SIZE * sizeof(char*));

    programs = (char***) malloc(numPrograms *sizeof(char**));
    for(int i = 0; i < numPrograms; i++){
        programs[i] = (char**) malloc(ARGS_BUFFER_SIZE * sizeof(char*));
    }

    /* Init. inFilePtr to null by default */
    FILE *inFilePtr;

    // Retrieve input file name
    inFileName = argv[1];

    // Attempt to open input file and switch context of stdin
    inFilePtr = freopen(inFileName, "r", stdin);

    // Check if input file exists, exit otherwise
    if(inFilePtr == NULL){
		fprintf(stderr, "freopen() failed to open file %s\n", inFileName);

        //Now we can start deallocating our pid_t and programs array
        for(int i = 0; i < numPrograms; i++){
            //free(pid[i]);
            free(programs[i]);
        }
        free(programs);
        free(pid);
        free(args);
        free(currentLinePtr);
        free(lineSavePtr);
        exit(EXIT_FAILURE);
    }

    /* ----------------------------------------------------------- */
    /* 1. Read the program workload from the specified input file. */
    /* ----------------------------------------------------------- */
    
    // Main run cycle
    for(lineCounter = 0; lineCounter < numPrograms; lineCounter++)
    {
        // Get input from input file line by line until there are no more lines
        getline(&currentLinePtr, &programsBufferSizeHolder, stdin);

        // Strip newline at the end of the input string
        currentLinePtr[strlen(currentLinePtr) - 1] = '\0';

        // save copy of currentLinePtr
        *lineSavePtr = currentLinePtr;

        /* Tokenize each line by space */
        numArgs = 0;
        while((cmdPtr = strtok_r(*lineSavePtr, " ", lineSavePtr))){

            // Next, save copy of current command
            args[numArgs] = cmdPtr;

            // Copy Current args values to programs[lineCounter];
            // strcpy(programs[lineCounter][numArgs], args[numArgs]);

            numArgs++;
        
        }

        // Replace last arg in args with null string
        args[numArgs] = (char*) NULL;

        
        // DEBUG: Print current program with arguments
        fprintf(stdout, "program[%i]\n", lineCounter);
        for(int i = 0; i <= numArgs; i++){
            fprintf(stdout, "arg[%i] %s\n", i, args[i]);
        }
        fprintf(stdout, "\n");
        

        
        // Now that we've gathered the current command it's time to fork shit up
        pid[lineCounter] = fork();

        // Case where new process wasn't created correctly
        if (pid[lineCounter] < 0) {
            fprintf(stderr, "ERROR! Unable to fork program[%i]: %s.\n", lineCounter, args[0]);

            //Now we can start deallocating our pid_t and programs array
            for(int i = 0; i < numPrograms; i++){
                //free(pid[i]);
                free(programs[i]);
            }
            free(programs);
            free(pid);
            //free(programs);

            // Free allocated memory
            free(currentLinePtr);
            free(lineSavePtr);
            free(args);
            exit(-1);
        }

        // Case where child is parent
        else if (pid[lineCounter] == 0) {
            // Make exec call
            execvp(args[0], args);
            //Now we can start deallocating our pid_t and programs array
            for(int i = 0; i < numPrograms; i++){
                //free(pid[i]);
                free(programs[i]);
            }

            free(programs);
            free(pid);
            //free(programs);

            // Free allocated memory
            free(currentLinePtr);
            free(lineSavePtr);
            free(args);

            // Exit when finished
            exit(-1);
        }
        
    }

    
    // Wait on remaining processes to finish
    for(int i = 0; i < numPrograms; i++){
        waitpid(pid[i], &status, 0);
    }

    //Now we can start deallocating our pid_t and programs array
    for(int i = 0; i < numPrograms; i++){
        //free(pid[i]);
        free(programs[i]);
    }
    free(programs);
    free(pid);
    //free(programs);

    // Free allocated memory
    free(currentLinePtr);
    free(lineSavePtr);
    free(args);
    //free(programs);




    /* 2. For each program, MCP mush launch program to run as separate process
    using some variant of fork(2) and one of the exec() system calls. */

    /* 3. Once all of the programs are running, MCP must wait for each program to
    terminate using the system call wait(). */

    /* 4. After all programs have terminated, MCP must exit using the exit() 
    system call. */

}