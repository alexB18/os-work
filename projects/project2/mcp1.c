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

int copyStringArray(char *** source, char*** destination, int arraySize){

    //First allocate the memory required for this particular 

    for(int i = 0; i < arraySize; i++){

        if(strcpy(*destination[i], *source[i]) != 0){
            fprintf(stderr, "ERROR! Unable to copy string array.\n");
            return -1;
        }
    }

    return 0;
}
/*---------------------------------------------------------------------------*/

int main(int argc, char** argv){

    /* Main Function Variables */
    int numLineCharacters, lineCounter, numCommands, numArgs, numPrograms, i;
    char *currentLinePtr, *inFileName, *cmdPtr, *arg, **lineSavePtr, **cmdSavePtr, **args, ***programs;

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
        numLineCharacters = getline(&currentLinePtr, &programsBufferSizeHolder, stdin);

        // Strip newline at the end of the input string
        currentLinePtr[strlen(currentLinePtr) - 1] = '\0';

        // save copy of currentLinePtr
        *lineSavePtr = currentLinePtr;

        /* Tokenize each line by semicolon */
        numCommands = 0;
        while((cmdPtr = strtok_r(*lineSavePtr, ";", lineSavePtr))){

            // Next, save copy of current command
            *cmdSavePtr = cmdPtr;

            // Tokenize each command by space
            numArgs = 0;
            while((arg = strtok_r(*cmdSavePtr, " ", cmdSavePtr)) && (numLineCharacters != -1)){


                // DEBUG: print each token
                //fprintf(stdout, "Line[%i], Command[%i], Arg[%i]: %s\n", lineCounter, numCommands, numArgs, arg);

                // DEBUG: print which arg is being added along with numArgs
                //fprintf(stdout, "numArgs[%i]: %s\n", numArgs, arg);
                
                // Add arg to collection of args
                args[numArgs] = arg;

                numArgs++;
            }

            // Copy Current args values to programs[numCommands];
            copyStringArray(&args, &programs[numCommands], numArgs);

            // DEBUG: Print current program with arguments
            
            
            fprintf(stdout, "program[%i]\n", numPrograms);
            for(int i = 0; i < numArgs ; i++){
                fprintf(stdout, "arg[%i] %s\n", i, programs[numPrograms][i]);
            }
            fprintf(stdout, "\n");
            
            


            // increment global numPrograms and local numCommands
            numPrograms ++;
            numCommands++;
        }
        lineCounter++;
    }while (numLineCharacters != -1);

    
    //fprintf(stdout, "Line[%i], Command[%i], Arg[%i]: %s\n", lineCounter, numCommands, numArgs, arg);

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
    free(args);
    free(programs);




    /* 2. For each program, MCP mush launch program to run as separate process
    using some variant of fork(2) and one of the exec() system calls. */

    /* 3. Once all of the programs are running, MCP must wait for each program to
    terminate using the system call wait(). */

    /* 4. After all programs have terminated, MCP must exit using the exit() 
    system call. */

}