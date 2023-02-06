#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

#define BUFFER_SIZE 80

int main (int argc, char *argv[])
{
	char    input[BUFFER_SIZE];
	int     i;
	int fd = STDIN_FILENO;

	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if(fd == -1)
		{
			write(STDERR_FILENO,"error",6);
			exit(EXIT_FAILURE);
		}
	}
	i = 0;
	while((i = read(fd ,input,BUFFER_SIZE)))
	{
		write(STDOUT_FILENO ,input,i);
	}
	close(fd);
}