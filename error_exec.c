#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main ()
{
	// char *command[] = {"grep" , "-E" , "c$" ,"-", 0 };
	// char *bin_file = command[0];
	 char *argv[] = { "ls", "-l", 0 };
    char *envp[] = { 0 };
	int fd = open ("redirect_.txt" , O_CREAT | O_TRUNC | O_WRONLY,0777);
	if (fd == -1)
	{
		perror("error opening file");
		exit(1);
	}

	if (fork() == 0)
	{
		dup2(fd,STDOUT_FILENO);
		close(fd);
		    if (execve("/bin/ls", argv, envp) == -1)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }
	}
	else
	{
		wait(NULL);
		close(fd);
		printf("done!\n");
	}

	return 0;
}


// int main()
// {
    // char *argv[] = { "ls", "-l", 0 };
    // char *envp[] = { 0 };

    // if (execve("/bin/ls", argv, envp) == -1)
    // {
    //     perror("execve");
    //     exit(EXIT_FAILURE);
    // }

//     return 0;
// }
