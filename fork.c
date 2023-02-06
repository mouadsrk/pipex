#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int id = fork();
	int n;
	int i;
	int t = 1;
	if (id == 0)
		n = 0;
	else{
		//  wait(0);
		n = 10;
	}
	i = n ;
	while(i < n + 5)
	{
		printf("%d ",i);
		fflush(stdout);
	i++;
	}	
	return (0);
}