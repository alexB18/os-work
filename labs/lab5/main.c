#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>

void sigusr1_handler (){
    /* This is an empty sig handler because we're only using SIGUSR1 to get a
    process to continue. Thus, our handler doesn't need to do anythin.
    */
}
/*---------------------------------------------------------------------------*/

void script_print (pid_t* pid_ary, int size){
   FILE* fout;
   fout = fopen ("top_script.sh", "w");
   fprintf(fout, "#!/bin/bash\ntop");
   for (int i = 0; i < size; i++){
      fprintf(fout, " -p %d", (int)(pid_ary[i]));
   }
   fprintf(fout, "\n");
   fclose (fout);
}

void signaller (pid_t* pids, int numProgs, int SIGNAL){

   //
   char* signal_str = strdup(sys_siglist[SIGNAL]);
   if(!signal_str){
      fprintf(stderr, "Error sending signal.\n");
      exit(EXIT_FAILURE);
   }

   //upcase(signal_str);
   int i;
   for(i = 0; i < numProgs; i++){
      // loop through each child and send signal
   sleep(2);
      fprintf(stdout, "\nParent process : <%d> - Sending signal: <%s> to child process: <%d>\n", getpid(), signal_str, pids[i]);
      kill(pids[i], SIGNAL);
      //fprintf(stdout, "Child process: %d - Received signal: <%s>.\n", pids[i], signal_str);   
   }

   free(signal_str);
   

}

int main(int argc, char** argv){

   // Initialize signal set
   sigset_t set;
   int sig;
   sigemptyset(&set);
   sigfillset(&set);

   // Register SIGUSR1 signal with appropriate handler
   signal(SIGUSR1, sigusr1_handler);

   if(argc == 1){
      fprintf(stderr, "Correct Usage: ./a.out [number of proccesses]\n");
      exit(EXIT_FAILURE);
   }

   int numProgs = atoi(argv[1]);
   int status = 0;

   // int describing process idS
   pid_t* pids = (pid_t*) malloc(numProgs * sizeof(pid_t));

   char **args;
   args = (char**) malloc(4 * sizeof(char*));
   args[0] = "./iobound";
   args[1] = "-seconds";
   args[2] = "30";
   args[3] = (char*) NULL;
   //args[3] = "test";
   
   printf("Main starting, my pid is %d\n\n", getpid ());
   for(int i = 0; i < numProgs; i++){

      // Case where pid is child
      if((pids[i] = fork()) == 0){
         fprintf(stdout, "Child Process: %d - Waiting for SIGUSR1...\n", getpid());
      
         // Wait for SIGUSR1
         int status = sigwait(&set, &sig);
         // If the status isn't 0, there's been some sort of error

         if(status != 0){
            fprintf(stderr, "Sigwait error with process: %d\n", getpid());
            exit(EXIT_FAILURE);
      
         //Otherwise make the exec call
         } else {

            fprintf(stdout, "Child Process: %d - Received signal: SIGUSR1 - Calling exec()\n", getpid());

            //exec
            execvp(args[0], args);

            // Exit when finished
            exit(-1);
         }
      
      }

      
   }

   signaller(pids, numProgs, SIGUSR1);

   signaller(pids, numProgs, SIGSTOP);
   sleep(5);

   signaller(pids, numProgs, SIGCONT);
   sleep(3);

   signaller(pids, numProgs, SIGINT);


   
   //Wait on remaining processes to finish
   for(int i = 0; i < numProgs; i++){

      waitpid(pids[i], &status, 0);
   }
   

   fprintf(stdout, "\n ALL PROCESSES FINISHED\n");


   printf("Main exiting, my pid is %d\n\n", getpid ());

   free(args);
   free(pids);

   exit(EXIT_SUCCESS);
   
   
}
