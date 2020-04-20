#include "command.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Helper function for counting number of characters in a string */
ssize_t numCharacters(char* inputStr){
    size_t i = 0;
    size_t count = 0;

    while (inputStr[i] != '\0'){
        count++;
        i++;
    }

    return count;
}

/*for the ls command*/
void listDir(){

    // Declare pointer which will hold current entry in directory
    struct dirent* directoryEntryPtr;

    // Attempt to open the current directory
    DIR* directoryStream = opendir(".");
    if(directoryStream == NULL){
        perror("Failed to open current directory.\n");
        return;
    }

    size_t count;
    while((directoryEntryPtr = readdir(directoryStream)) != NULL){

        //Retrieve number of characters in the name of directory item
        count = numCharacters(directoryEntryPtr->d_name);

        //write contents name of current directory item to stdout
        if( write(1, directoryEntryPtr->d_name, count) == -1){
            perror("Error writing directory item name to stdout.\n");
            return;
        }
        write(1, " ", 1);
    }
    write(1, "\n", 1);

    //Close directory
    closedir(directoryStream);
}

/*for the pwd command*/
void showCurrentDir(){

        
    // Initialize function variables
    char* pathBufferPtr;
    ssize_t pathBufferSize = 100;
    size_t count;

    // Allocate memory for the pathBufferPtr
    pathBufferPtr = (char*) malloc(pathBufferSize * sizeof(char));

    // Get current working directory and store in pathBufferPtr
    getcwd(pathBufferPtr, pathBufferSize);
    
    // Retrieve number of characters in the directory
    count = numCharacters(pathBufferPtr);

    // write contents of directory to stdout
    if( write(1, pathBufferPtr, count) == -1){
        perror("Error writing cwd to stdout.\n");
        return;
    }
    write(1, "\n", 1);

    // Free allocated memory
    free(pathBufferPtr);

}

/*for the mkdir command*/
void makeDir(char *dirName){

    // mkdir returns -1 if it ran into an error
    if(mkdir(dirName, 0777) == -1){
        perror("Error! Unable to create directory");
    }

}

/*for the cd command*/
void changeDir(char *dirName){
    
    //chdir returns -1 if it ran into an error
    if(chdir(dirName) == -1){
        perror("Error! Unable to change directory");
    }
    
}

/*for the cp command*/
void copyFile(char *sourcePath, char *destinationPath){

    int sourceFileDescriptor, destinationFileDescriptor;
    size_t bytesRead;
    char* buffer[2048];

    // Attempt to open source file
    sourceFileDescriptor = open(sourcePath, O_RDONLY);
    if(sourceFileDescriptor == -1){
        perror("Error! Unable to open file to be copied");
        return;
    }

    // Attempt to open destination file
    // The O_CREAT / O_TRUNC truncates existing file or creates a new one if need
    // The rest are for permissions
    destinationFileDescriptor = open(destinationPath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWGRP |  S_IWUSR | S_IRGRP | S_IROTH | S_IWOTH);
    if(sourceFileDescriptor == -1){
        perror("Error! Unable to open destination file");
        close(destinationFileDescriptor);
        return;
    }

    // Transfer data from the source file to the destination file until end
    while((bytesRead = read(sourceFileDescriptor, buffer, 2048)) > 0){
        if(write(destinationFileDescriptor, buffer, bytesRead) != bytesRead){
            perror("Error! Unable to write data to destination file");
        }
    }

    close(sourceFileDescriptor);
    close(destinationFileDescriptor);

    return;

}

/*for the mv command*/
void moveFile(char *sourcePath, char *destinationPath){

    int sourceFileDescriptor, destinationFileDescriptor;
    size_t bytesRead;
    char* buffer[2048];

    // Attempt to open source file
    sourceFileDescriptor = open(sourcePath, O_RDONLY);
    if(sourceFileDescriptor == -1){
        perror("Error! Unable to open file to be moved");
        return;
    }

    // Attempt to open destination file
    // The O_CREAT / O_TRUNC truncates existing file or creates a new one if need
    // The rest are for permissions
    destinationFileDescriptor = open(destinationPath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWGRP |  S_IWUSR | S_IRGRP | S_IROTH | S_IWOTH);
    if(sourceFileDescriptor == -1){
        perror("Error! Unable to create destination file");
        close(destinationFileDescriptor);
        return;
    }

    // Transfer data from the source file to the destination file until end
    while((bytesRead = read(sourceFileDescriptor, buffer, 2048)) > 0){
        if(write(destinationFileDescriptor, buffer, bytesRead) != bytesRead){
            perror("Error! Unable to write data to destination file");
        }
    }

    close(sourceFileDescriptor);
    close(destinationFileDescriptor);

    // Delete source file
    //unlink returns -1 if it ran into an error
    if(unlink(sourcePath) == -1){
        perror("Error! Unable to delete file");
    }


}

/*for the rm command*/
void deleteFile(char *filename){

    //unlink returns -1 if it ran into an error
    if(unlink(filename) == -1){
        perror("Error! Unable to delete file");
    }

}

/*for the cat command*/
void displayFile(char *filename){

    // small/non-negative int which will be used to refer to opened file
    int currentFileDescriptor;
    size_t bytesRead;   // int which refers to the exact number of bytes read by read()
    char contents[currentFileDescriptor];   // string containing the contents of the file

    // Open the file in "read only" mode
    currentFileDescriptor = open(filename, O_RDONLY);

    // Check to see if file was opened correctly
    if(currentFileDescriptor == -1){
        perror("Error! Unable to open file");
    
    } else {
        bytesRead = read(currentFileDescriptor, contents, sizeof(contents) - 1);
        write(1, contents, bytesRead);
        write(1, "\n", 1);
        close(currentFileDescriptor);
    }
}