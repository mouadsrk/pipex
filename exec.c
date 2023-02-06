#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

int main ()
{
	char *command[] = {"grep" , "-E" , "c$" ,"-", 0 };
	char *bin_file = command[0];
	execvp (bin_file,command); 
}
