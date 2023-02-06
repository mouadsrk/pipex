#ifndef PIPEX_H
#define	PIPEX_H
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

typedef struct var_s
{
	int n;
	char **arg;
	char *env;
	int fd[2];
	int p1fd;
	int p1pid;
	int p2pi

}t_vars;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
#endif

