#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    // Check for the correct number of command line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pipe_fd>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

	// Convert the pipe file descriptor from string to integer
    int pipe_fd = atoi(argv[1]);

    //Get the character from the user
    char character;
	int scanret = scanf("%1s", &character);
	if (scanret != 1) exit(EXIT_FAILURE);
	
    // Write the character to the pipe
    int writeret = write(pipe_fd, &character, 1);
	if (writeret != 1) exit(EXIT_FAILURE);
	
	// Close the write end of the pipe in the child
    close(pipe_fd); 
    
	exit(EXIT_SUCCESS);
}