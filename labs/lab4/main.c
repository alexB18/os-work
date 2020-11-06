#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void script_print (pid_t* pid_ary, int size){
    FILE* fout;
    fout = fopen ("top_script.sh", "w");
    fprintf(fout, "#!/bin/bash\ntop");
    for (int i = 0; i < size; i++){
        fprintf(fout, " -p %d", (int)(pid_ary[i]));
    }
    fprintf(fout, "\n");
    fclose (fout);}

int main(int argc, char** argv){

    if(argc == 1){
        fprintf(stderr, "Correct Usage: ./a.out [number of proccesses]\n");
        exit(EXIT_FAILURE);
    }

    int numProgs = atoi(argv[1]);
    int status = 0;
    pid_t* pids;
    pids = (pid_t*) malloc(numProgs * sizeof(pid_t));
    pid_t wpid;

    char **args;
    args = (char**) malloc(4 * sizeof(char*));
    args[0] = "./iobound";
    args[1] = "-seconds";
    args[2] = "5";
    args[3] = (char*) NULL;
    //args[3] = "test";
    
    printf("Main starting, my pid is %d\n\n", getpid ());
    for(int i = 0; i < numProgs; i++){

        // Case where pid is child
        if((pids[i] = fork()) == 0){
            printf("This is child process. my pid is %d. my parent's pid is %d\n\n", getpid(), getppid());
            //exec
            execvp(args[0], args);

            sleep(2);
        }
    }
    //

    // Wait on remaining processes to finish
    while((wpid = wait(&status)) > 0);
    printf("Main exiting, my pid is %d\n\n", getpid ());

    free(args);
    free(pids);
}
