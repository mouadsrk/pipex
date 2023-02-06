#include "pipex.h"

void ft_commande1(t_vars *v)
{
	int fd ;
	char **cmd;
	char *path;

	fd = open(v->arg[1],O_RDONLY,0777);
	cmd = ft_split(v->arg[2],' ');
	char *new_argv[] = {cmd, NULL };
    char *new_envp[] = { "PATH=/bin", "TERM=xterm", NULL };
	path = ft_strjoin("/bin/",cmd[0]);
    execve(path, new_argv, new_envp);			
}

void ft_commande2(t_vars *v)
{
	char *new_argv[] = { "pwd", NULL };
    char *new_envp[] = { "PATH=/bin", "TERM=xterm", NULL };

    execve("/bin/pwd", new_argv, new_envp);
}
void ft_pipex(t_vars *v)
{	
	pipe(v->fd);
	v->p1pid = fork();
	if(v->p1pid == 0)
	{
		close(v->fd[0]);
		dup2(v->fd[1],STDOUT_FILENO);
		ft_commande1(v);
	}
	else
		wait(NULL);
		ft_command2();
}

int main (int argc ,char **argv,char *envp[])
{
	t_vars *v;

    if(argc < 5)
		return 0;
	v->n= argc;
	v->arg = argv;
	v->env = envp;
	ft_pipex(v);
	return (0);
}