#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pid_t pid;
    int input_file, output_file;
    
    // Open input file for reading
    input_file = open("input.txt", O_RDONLY);
    if (input_file == -1) {
        perror("Error opening input file");
        exit(1);
    }
    
    // Create a pipe
    if (pipe(fd) == -1) {
        perror("Error creating pipe");
        exit(1);
    }
    
    // Create a child process
    pid = fork();
    if (pid == -1) {
        perror("Error creating child process");
        exit(1);
    }
    
    if (pid == 0) {
        // Child process
        // Close read end of the pipe
        close(fd[0]);
        
        // Redirect standard output to the write end of the pipe
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("Error redirecting output to pipe");
            exit(1);
        }
        
        // Close the write end of the pipe (no longer needed)
        close(fd[1]);
        
        // Copy input from file to pipe
        char buffer[1024];
        int n;
        while ((n = read(input_file, buffer, 1024)) > 0) {
            write(STDOUT_FILENO, buffer, n);
        }
        
        // Close input file
        close(input_file);
        
        exit(0);
    } else {
        // Parent process
        // Close write end of the pipe
        close(fd[1]);
        
        // Open output file for writing
        output_file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_file == -1) {
            perror("Error opening output file");
            exit(1);
        }
        
        // Copy from pipe to output file
        char buffer[1024];
        int n;
        while ((n = read(fd[0], buffer, 1024)) > 0) {
            write(output_file, buffer, n);
        }
        
        // Close output file
        close(output_file);
        
        // Wait for child process to finish
        wait(NULL);
        
        exit(0);
    }
}
