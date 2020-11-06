#include "command.h"
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Found this useful snippet on 
https://stackoverflow.com/questions/10347689/how-can-i-check-whether-a-string-ends-with-csv-in-c

Given a char* str and a char* suffix, returns an int between
0 and 1 corresponding to whether or not str ends with suffix
*/
int string_ends_with(const char* str, const char* suffix)
{
	int str_len = strlen(str);
	int suffix_len = strlen(suffix);

	return
		(str_len >= suffix_len) &&
		(0 == strcmp(str + (str_len - suffix_len), suffix));
}

void lfcat()
{
	// Define your variables here
	char* pathBufferPtr, *currentLine;
	FILE* inFilePtr;
	DIR* currentDirPtr;
	struct dirent* currentFilePtr;
	size_t bufferSize = 60;
	int numCharacters;

	// Allocate memory for the pathBufferPtr & currentLine
	pathBufferPtr = (char*) malloc(bufferSize * sizeof(char));
	currentLine = (char*) malloc(bufferSize * sizeof(char));

	// Get the current directory
	getcwd(pathBufferPtr, bufferSize);

	// Open the dir using opendir()
	currentDirPtr = opendir(pathBufferPtr);

	// use a while loop to read the dir
	while((currentFilePtr = readdir(currentDirPtr)) != NULL){

		//write(1, currentFilePtr->d_name, bufferSize);


		//fprintf(stdout,"name: %s\n",currentFilePtr->d_name);
		//fprintf(stdout,"type: %d\n",currentFilePtr->d_type);
		//fprintf(stdout, "\n");

		

		// Hint: use an if statement to skip any names that are not readable files (e.g. ".", "..", "main.c", "a.out", "output.txt"
		if
			(!
			((strcmp(currentFilePtr->d_name, "main.c") == 0) ||
			(strcmp(currentFilePtr->d_name, "main.o") == 0) ||
			(strcmp(currentFilePtr->d_name, "command.c") == 0) ||
			(strcmp(currentFilePtr->d_name, "command.h") == 0) ||
			(strcmp(currentFilePtr->d_name, "command.o") == 0) ||
			(strcmp(currentFilePtr->d_name, "lab3.exe") == 0) ||
			(strcmp(currentFilePtr->d_name, "lab3.pdf") == 0) ||
			(strcmp(currentFilePtr->d_name, ".") == 0) ||
			(strcmp(currentFilePtr->d_name, "..") == 0) ||
			(strcmp(currentFilePtr->d_name, "log.txt") == 0) ||
			(strcmp(currentFilePtr->d_name, "Makefile") == 0) ||
			(strcmp(currentFilePtr->d_name, "input.txt") == 0) ||
			(strcmp(currentFilePtr->d_name, "output.txt") == 0) ||
			(strcmp(currentFilePtr->d_name, "res_output.txt") == 0)
			))
		{
			
//fprintf(stdout,"Name: %s\n",currentFilePtr->d_name);
		write(1, "Name: ", sizeof("Name: "));
		write(1, currentFilePtr->d_name, sizeof(currentFilePtr->d_name+1));
		write(1, "\n", sizeof("\n"));
	
		
		// Open the file
		inFilePtr = fopen(currentFilePtr->d_name, "r");

		// Check if input file was succesffully opened
		if(inFilePtr == NULL){
			fprintf(stderr, "fopen() failed to open file %s\n", currentFilePtr->d_name);
			exit(EXIT_FAILURE);
		}

		//write(1, ("File: %s", currentFilePtr->d_name), bufferSize);
		// Read in each line using getline()
		while((numCharacters = getline(&currentLine, &bufferSize, inFilePtr)) != -1){
			// Write the line to stdout
			write(1, currentLine, numCharacters);
			//fprintf(stdout, "%s", currentLine);
		}

		// write 80 "-" characters to stdout
		for(int i = 0; i < 80; i++){
			write(1, "-", 1);
			//fprintf(stdout, "-");
		}
		write(1, "\n", 1);

		// close the read file and free/null assign your line buffer
		fclose(inFilePtr);
		//currentLine = NULL;
		}


	}

	free(pathBufferPtr);
	free(currentLine);

	//close the directory you were reading from using closedir()
	closedir(currentDirPtr);


}
