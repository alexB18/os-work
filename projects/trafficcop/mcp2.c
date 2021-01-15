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
#include <signal.h>

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


void sigusr1_handler (){
    /* This is an empty sig handler because we're only using SIGUSR1 to get a
    process to continue. Thus, our handler doesn't need to do anythin.
    */
}
/*---------------------------------------------------------------------------*/

int main(int argc, char** argv){

    /* Main Function Variables */
    int lineCounter, numArgs, numPrograms, status;
    char *currentLinePtr, *inFileName, *cmdPtr, **lineSavePtr, **args, ***programs;

    size_t programsBufferSizeHolder = PROGRAMS_BUFFER_SIZE;

    // Initialize signal set
    sigset_t set;
    int sig;
    sigemptyset(&set);
    sigfillset(&set);

    // Register SIGUSR1 signal with appropriate handler
    signal(SIGUSR1, sigusr1_handler);

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
            exit(-1);
        }

        // Case where process is child
        else if (pid[lineCounter] == 0) {

            //DEBUG: inform that process is waiting for SIGUSR1
            fprintf(stdout, "Child Process: %d - Waiting for SIGUSR1...\n", getpid());

            // Wait for SIGUSR1
            int status = sigwait(&set, &sig);
            if(status != 0){
                fprintf(stderr, "Sigwait error with process: %d\n", getpid());

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
            
            } else {

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

            /*
            // Attempt to add Signal SIGUSR1 to signal Set
            if(sigaddset(&set, SIGUSR1) == -1){
                fprintf(stderr, "Error with sigaddset.\n");
                exit(-1);
            }
            

            // Wait until SIGUSR1 signal is given before calling exec
            //DEBUG: inform that processes has just entered the sigwait loop
            fprintf(stdout, "Process: %i waiting for SIGUSR1.\n", getpid());
            while(1) {

                // Call sigwait and check for errors
                if(sigwait(&sigSet, &sig) != 0){
                    fprintf(stderr, "Error with sigwait in process: %i\n", getpid());
                    exit(-1);
                }

                //If sig received is SIGUSR1, break the loop;
                if(sig == SIGUSR1){
                  break;
                }
            }
            */

        }
        
    }
    sleep(1);

    // Send SIGUSR1 to once all are waiting proccess, indicating ready to call exec
    fprintf(stdout, "\n");
    for(int i = 0; i < numPrograms; i ++){
        kill(pid[i], SIGUSR1);
        fprintf(stdout, "Process: %d - Received signal: SIGUSR1 - Calling exec().\n", pid[i]);

    }
    fprintf(stdout, "\n");

    // Once all processes up and running, we want to suspend them
    for(int i = 0; i < numPrograms; i++){
        kill(pid[i], SIGSTOP);
        fprintf(stdout, "Process: %d received SIGSTOP. Waiting...\n", pid[i]);
    }
    fprintf(stdout, "\n");
    sleep(15);

    // Once they've been suspended, we want to resume them
    for(int i = 0; i < numPrograms; i++){
        kill(pid[i], SIGCONT);
        fprintf(stdout, "Process: %d received SIGCONT. Resuming...\n", pid[i]);

    }
    fprintf(stdout, "\n"); 
    
    // Wait on remaining processes to finish
    for(int i = 0; i < numPrograms; i++){

        // Wait until the process is finished executing
        waitpid(pid[i], &status, 0);
    }

    fprintf(stdout, "\n ALL PROCESSES FINISHED\n");

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