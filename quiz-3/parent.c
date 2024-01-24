#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int status;
    char characters[4];
	
	//User Prompt
	printf("Enter four characters, followed by ENTER for !EACH!\n");
	
    int pipe_fd[2];

    // Create a pipe for communication
    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    // Fork 4 times
    for (int i = 0; i < 4; ++i) {
        pid_t pid = fork();

        // Check for fork error
        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
			
			// Close the read end of the pipe in the child
            close(pipe_fd[0]); 

            // Convert the pipe file descriptor to a string
            char pipe_fd_str[10];
            snprintf(pipe_fd_str, sizeof(pipe_fd_str), "%d", pipe_fd[1]);

            // Execute the child program with the pipe file descriptor as an argument
            execlp("./child", "child", pipe_fd_str, NULL);
            
            // Print error if exec fails
            perror("Exec failed"); 	//this and the next line are not executed
            exit(EXIT_FAILURE);		//unless execlp failure
        }
    }

    // Parent waits for all children to finish
    for (int i = 0; i < 4; ++i) {
        wait(&status);
    }

	// Close the write end of the pipe in the parent
    close(pipe_fd[1]);
	
    // Parent process
    for (int i = 0; i < 4; ++i) {
        // Read the character from the pipe
        ssize_t bytesRead = read(pipe_fd[0], &characters[i], 1);
		
		//If error reading then exit
		if (bytesRead == -1) {
			perror("Read error");
			exit(EXIT_FAILURE);
		}

        printf("This is child process %d and my character was %c.\n", i + 1, characters[i]);
    }

	// Close the read end of the pipe in the parent
    close(pipe_fd[0]); 

    return 0;
}

