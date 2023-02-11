/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:42:52 by mserrouk          #+#    #+#             */
/*   Updated: 2023/02/11 18:39:58 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_all_paths(char *envp[])
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (ft_split(envp[i] + 5, ':'));
	}
	return (NULL);
}

void	ft_command_path(t_vars *v, char *argv)
{
	int	i;

	i = 0;
	v->cmd1 = ft_split(argv, ' ');
	while (v->paths[i])
	{
		v->cmdpath = ft_strjoin(v->paths[i], v->cmd1[0]);
		if (!access(v->cmdpath, R_OK))
			return ;
		free(v->cmdpath);
		v->cmdpath = NULL;
		i++;
	}
	error_message("command no fond");
}

void	ft_pipex_25line(t_vars *v, char **argv)
{
	if (v->p2pid == 0)
	{
		ft_command_path(v, argv[3]);
		ft_command2(v, argv);
	}
	close(v->fd[0]);
	close(v->fd[1]);
}

void	ft_pipex(t_vars *v, char **argv)
{
	if (pipe(v->fd) == -1)
		error_message("Error creating pipe");
	ft_command_path(v, argv[2]);
	if (!v->cmdpath)
		error_message("Error command not found");
	ft_free(v->cmd1, ft_word(argv[2], ' '));
	free(v->cmdpath);
	ft_command_path(v, argv[3]);
	if (!v->cmdpath)
		error_message("Error command not found");
	free(v->cmdpath);
	ft_free(v->cmd1, ft_word(argv[3], ' '));
	v->p1pid = fork();
	if (v->p1pid == -1)
		error_message("Error creating child process");
	if (v->p1pid == 0)
	{
		ft_command_path(v, argv[2]);
		ft_command1(v, argv);
	}
	v->p2pid = fork();
	if (v->p2pid == -1)
		error_message("Error creating child process");
	else
		ft_pipex_25line(v, argv);
}

int	main(int argc, char **argv, char *envp[])
{
	t_vars	v;

	if (argc != 5)
		error_message("error in argument");
	v.paths = ft_all_paths(envp);
	ft_pipex(&v, argv);
	wait(NULL);
	wait(NULL);
	return (0);
}
