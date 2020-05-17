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

// int array holding all pid's currently in the workload. Is allocated in main.
pid_t* pid;

// int array holding the exited of all pid's currently in the workload. Is allocated in main
int* exited;
// tallies the total number of programs which have exited.
int numExited = 0;
// int describing the index of the process which is currently in execution
int activeProcessIndex = 0;



// int representing the total number of programs in workload. Initialized in main.
int numPrograms;
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
/*----------------------------------------------------------------------------*/

/*-----------------------------Handler Functions------------------------------*/
void sigusr1_handler (){
    /* This is an empty sig handler because we're only using SIGUSR1 to get a
    process to continue. Thus, our handler doesn't need to do anythin.
    */
}


void sigalrm_handler(){
    /* When the SIGALRM signal is delivered, the MCP will be interrupted and the signal 
    handling function will be executed. The following will happen when th signal 
    handler is called:
    
    1.The MCP will suspend the running workload process.
    2.The MCP decides on the next workload process to run, and sends it a ​SIGCONT​ signal.
    3.The MCP will reset the alarm, and continue with whatever else it was doing
    */

    // Suspend the currently running process
    kill(pid[activeProcessIndex], SIGSTOP);

    fprintf(stdout, "\nProcess: %d paused...\n", pid[activeProcessIndex]);
    fprintf(stdout, "Num Exited: %d\n", numExited);


    // Decide on the next process to run, and sent it a SIGCONT signal

    /*
       The simplest method is just to schedule the next process in the
       pid array... so that's what imma do.
    */
    int isFinished;
    int isStopped;
    int status;
    //int lock = 1;
    while(1) {

        waitpid(pid[activeProcessIndex], &status, WNOHANG);
        isFinished = WIFEXITED(status);
        isStopped = WIFSTOPPED(status);
        //fprintf(stdout, "isFinished: %i\n", status);

        // If the current process is dead, and we don't already know about it,
        // We need to continue and mark it/update...
        if((isFinished) && (exited[activeProcessIndex] == 0)){

            exited[activeProcessIndex] = 1;

            // But we need to ake sure the active process index doesn't get bigger than numPrograms
            if(activeProcessIndex == (numPrograms - 1)){
                activeProcessIndex = 0;
            
            } else {
                activeProcessIndex++;
            }

            numExited ++;
            continue;
        
        // If the current process is dead, and we knew about it, just continue...
        } else if(isFinished){

            // But we need to ake sure the active process index doesn't get bigger than numPrograms
            if(activeProcessIndex == (numPrograms - 1)){
                activeProcessIndex = 0;
            
            } else {
                activeProcessIndex++;
            }

            continue;
        
        
        // Else the process is alive and we can start it up...
        } else {

            if(numExited != (numPrograms - 1)){
                kill(pid[activeProcessIndex], SIGCONT);
                fprintf(stdout, "Process: %d resumed...\n", pid[activeProcessIndex]);
                
                // But we need to ake sure the active process index doesn't get bigger than numPrograms
                if(activeProcessIndex == (numPrograms - 1)){
                    activeProcessIndex = 0;
            
                } else {
                    activeProcessIndex++;
                }

                alarm(2);
                return;
            
            // If it is, just resume it and don't call alarm
            } else {
                kill(pid[activeProcessIndex], SIGCONT);
                fprintf(stdout, "Process: %d resumed...\n", pid[activeProcessIndex]);
                
                
                // But we need to ake sure the active process index doesn't get bigger than numPrograms
                if(activeProcessIndex == (numPrograms - 1)){
                    activeProcessIndex = 0;
            
                } else {
                    activeProcessIndex++;
                }
                return;
            }
        }





    }

}
/*---------------------------------------------------------------------------*/

int main(int argc, char** argv){

    /* Main Function Variables */
    int lineCounter, numArgs, status;
    char *currentLinePtr, *inFileName, *cmdPtr, **lineSavePtr, **args, ***programs;

    size_t programsBufferSizeHolder = PROGRAMS_BUFFER_SIZE;

    // Initialize signal set
    sigset_t set;
    int sig;
    sigemptyset(&set);

    sigaddset(&set, SIGSTOP);
    sigaddset(&set, SIGCONT);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGALRM);
    //sigfillset(&set);

    // Register SIGUSR1 and SIGALRM signals with appropriate handlers
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGALRM, sigalrm_handler);

    // DEBUG: Print number of detected lines (programs)
    numPrograms = countlines(argv[1]);
    if(numPrograms == -1 ){
        exit(EXIT_FAILURE);
    
    } else {
        fprintf(stdout, "Number of programs: %i\n", numPrograms);
    }

    // Now that we have numPrograms, allocate necessary size in pid array
    pid = (pid_t*) malloc(numPrograms * sizeof(pid_t));
    // Do the same for the exit  array:
    exited = (int *) malloc(numPrograms * sizeof(int));

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

            // Set exited status of process to 0 as it is starting execution
            exited[lineCounter] = 0;

            // Wait for SIGUSR1
            status = sigwait(&set, &sig);
            //fprintf(stdout, "Alarm reached in process: %d\n", getpid());
            if(status != 0){
                fprintf(stderr, "Alarm error with process: %d\n", getpid());
                exit(-1);
            
            } else {

                // Make exec call
                execvp(args[0], args);

                // Once the exec call has finished, set the exited status of process to 1
                // as it has finished execution
                exited[lineCounter] = 1;
                numExited ++;

                /*
                    This print statement gets reached but these values ^^^ stay unchanged
                */

                

                // Exit when finished
                exit(-1);
            }
        }
    }
    sleep(1);

    // Once all processes are ready to hit exec, we want to suspend them for the time being
    fprintf(stdout, "\n");
    for(int i = 0; i < numPrograms; i++){
        kill(pid[i], SIGUSR1);
        kill(pid[i], SIGSTOP);
        fprintf(stdout, "Process: %d received SIGSTOP. Waiting...\n", pid[i]);
    }
    fprintf(stdout, "\n");
    sleep(1);

    // Now are ready to be scheduled
    /*

        1. Call alarm(1)*
        2.  then wait for all children to finish
        2.a (During this time alrm handler will be triggered)

        (Check if children are alive);
        (PUT ALARM IN HANDLER)
    */
    alarm(2);
    for(int i = 0; i < numPrograms; i++){
        waitpid(pid[i], &status, 0);
    }

    fprintf(stdout, "\n ALL PROCESSES FINISHED\n");

    //Now we can start deallocating our pid_t and programs array
    for(int i = 0; i < numPrograms; i++){
        free(programs[i]);
    }

    // Free allocated memory
    free(programs);
    free(pid);
    free(exited);
    free(currentLinePtr);
    free(lineSavePtr);
    free(args);
}