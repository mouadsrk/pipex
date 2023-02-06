#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>


int main()
{
    int i = fork();
    // if(i == 0)
    // {
    //     wait(0);
    //     // printf("%d\n",i);
    // }
    printf("current id = %d parent id = %d\n",getpid(),getppid());

}