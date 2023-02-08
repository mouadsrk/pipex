#include "pipex.h"

char **ft_all_paths(char *envp[])
{
	int i;

	i = -1;
	while(envp[++i])
	{
		if(ft_strnstr(envp[i],"PATH",4))
			return ft_split(envp[i] + 5, ':');
	}
	return NULL;
}

void ft_path(t_vars *v,char *argv)
{
	int i;

	i = 0;
	v->cmd1 = ft_split(argv,' ');
	while (v->paths[i])
	{
		v->cmdpath = ft_strjoin(v->paths[i], v->cmd1[0]);
		if(!access(v->cmdpath,R_OK))
		{
			break;
		}
		free(v->cmdpath);
		i++;
	}
}

void ft_commande1(t_vars *v,char **argv)
{
	int	fdinput;

	fdinput = open(argv[1],O_RDONLY,0777);
	if (fdinput == -1) {
        perror("Error opening input file");
        exit(1);
    }
	dup2(fdinput,STDIN_FILENO);
	dup2(v->fd[1],STDOUT_FILENO);
	close(v->fd[1]);
	close(fdinput);
    execve(v->cmdpath, v->cmd1, NULL);
}


void ft_commande2(t_vars *v,char **argv)
{
	int	fd;

	fd = open(argv[4],O_WRONLY | O_TRUNC,0777);
	if (fd == -1) {
        perror("Error opening input file");
        exit(1);
    }
	// int	fdinput;

	// fdinput = open(argv[1],O_RDONLY ,0777);
	// if (fdinput == -1) {
    //     perror("Error opening input file");
    //     exit(1);
    // }
	// 	char buffer[10];
    //     int n;
	// 	n = 1;
	// 	int i = 0;
    // while ((n = read(v->fd[0], buffer, 10)) > 0 && i++ <30)
	// {
    //     // write(1, buffer, n);
	// }
	dup2(v->fd[0],STDIN_FILENO);
	dup2(fd,STDOUT_FILENO);
	close(v->fd[1]);
	close(fd);
	close(v->fd[0]);
    execve(v->cmdpath, v->cmd1, NULL);
}

void ft_pipex(t_vars *v, char **argv)
{
	int status;

	if (pipe(v->fd) == -1) {
        perror("Error creating pipe");
        exit(1);
	}
	v->p1pid = fork();
    if (v->p1pid == -1) {
        perror("Error creating child process");
        exit(1);
    }
	if(v->p1pid == 0)
	{
		close(v->fd[0]);
		ft_path(v,argv[2]);
		ft_commande1(v,argv);
	}
	else
	{
		wait(0);
		ft_path(v,argv[3]);
		ft_commande2(v,argv);
		exit(0);
	}	
}

int main (int argc ,char **argv,char *envp[])
{
	t_vars v;
	int i = 0;
    if(argc < 5)
		return 0;
	v.paths=ft_all_paths(envp);
	ft_pipex(&v,argv);
	return (0);
}
