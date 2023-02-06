#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int ac ,char **av)
{
    char *comand[] = {"grep","-E","c",0};
    char *first_arg = comand[0];
   
   if (fork() == 0)
   {
      int fd = open("rest.txt",O_CREAT | O_TRUNC | O_WRONLY ,777);
      if(fd == -1)
      fprintf(stderr, "error in fd%d \n", fd);
      dup2(fd,1);
      if(execvp(first_arg , comand) == -1)
      fprintf(stderr, "error executing %s \n",first_arg);
      printf("done!\n");
   }
   else
   wait(NULL);
   printf("done!\n");
}