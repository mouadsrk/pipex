#ifndef PIPEX_H
#define	PIPEX_H


#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#define BUFFER_SIZE 42

typedef struct var_s
{
	char	**paths;
	char	*cmdpath;
	char	**cmd1;
	int		fd[2];
	int		p1fd;
	int		p1pid;
	int		p2pi;
	int		p2fd;

}t_vars;

char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
#endif
