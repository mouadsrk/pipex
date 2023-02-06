#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
    // printf("Before execve()\n");
    // printf("Program name: %s\n", argv[0]);

    char *new_argv[] = { "pwd", NULL };
    char *new_envp[] = { "PATH=/bin", "TERM=xterm", NULL };

    execve("/bin/pwd", new_argv, new_envp);

    // This line will not be executed 
    printf("After execve()\n");
    return 0;
}
