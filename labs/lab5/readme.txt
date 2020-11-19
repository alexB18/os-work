To run, type "make" and then type ./lab5 <number of processes>.

The program will then spawn the number of processes you specified,
send them all a SIGUSR1 signal, then will send them all SIGSTOP and
SIGCONT. Following this, the main processes will send SIGINT to all
of its children to murder them.