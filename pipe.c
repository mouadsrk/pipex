#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int fd[2];
    pid_t pid;
    char buffer[30];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(fd[0]);
        write(fd[1], "Hello, World!", 14);
        close(fd[1]);
        exit(EXIT_SUCCESS);
    } else {
        close(fd[1]);
        int i = read(fd[0], buffer, 14);

        printf("i = %dReceived: %s\n",i, buffer);
        close(fd[0]);
        wait(NULL);
    }

    return 0;
}
