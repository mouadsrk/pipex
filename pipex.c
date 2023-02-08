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

void ft_command_path(t_vars *v,char *argv)
{
	int i;

	i = 0;
	v->cmd1 = ft_split(argv,' ');
	while (v->paths[i])
	{
		v->cmdpath = ft_strjoin(v->paths[i], v->cmd1[0]);
		if(!access(v->cmdpath,R_OK))
		{
			return ;
		}
		free(v->cmdpath);
		v->cmdpath= NULL;
		i++;
	}
}

void ft_command1(t_vars *v,char **argv)
{
	int	fdinput;

	fdinput = open(argv[1],O_RDONLY,0777);
	if (fdinput == -1) {
        perror("Error opening input file");
        exit(1);
    }
	if (dup2(fdinput,STDIN_FILENO) == -1)
		{
			exit(1);
		}
	if (dup2(v->fd[1],STDOUT_FILENO)== -1)
	{
			exit(1);
	}
	close(v->fd[0]);
	close(v->fd[1]);
	close(fdinput);
    execve(v->cmdpath, v->cmd1, NULL);
}


void ft_command2(t_vars *v,char **argv)
{
	int	fd;

	fd = open(argv[4],O_WRONLY | O_TRUNC,0777);
	if (fd == -1) {
        perror("Error opening input file");
        exit(1);
    }
	if (dup2(v->fd[0],STDIN_FILENO) == -1)
	{
			exit(1);
	}
	if (dup2(fd,STDOUT_FILENO) == -1)
	{
			exit(1);
	}
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
		ft_command_path(v,argv[2]);
		ft_command1(v,argv);
	}
	else
	{
		wait(0);
		ft_command_path(v,argv[2]);
		if(!v->cmdpath)
		{
			write(2,"command not found:",20);
			write(2,v->cmd1[0],ft_strlen(v->cmd1[0]));
			exit(1);
		}
		ft_command_path(v,argv[3]);
		if(!v->cmdpath)
		{
			write(2,ft_strjoin("command not found:",v->cmd1[0]),20 + ft_strlen(v->cmd1[0]));
			// write(2,v->cmd1[0],ft_strlen(v->cmd1[0]));
			exit(1);
		}

		ft_command2(v,argv);
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
