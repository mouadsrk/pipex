/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:42:52 by mserrouk          #+#    #+#             */
/*   Updated: 2023/02/10 19:27:46 by mserrouk         ###   ########.fr       */
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
		{
			return ;
		}
		free(v->cmdpath);
		v->cmdpath = NULL;
		i++;
	}
}

void	ft_pipex_25line(t_vars *v, char **argv)
{
	wait(0);
	ft_command_path(v, argv[2]);
	if (!v->cmdpath)
		error_message("error");
	free(v->cmdpath);
	free(v->cmd1[0]);
	free(v->cmd1);
	ft_command_path(v, argv[3]);
	if (!v->cmdpath)
		error_message("Error creating pipe");
	ft_command2(v, argv);
}

void	ft_pipex(t_vars *v, char **argv)
{
	int	status;

	if (pipe(v->fd) == -1)
		error_message("Error creating pipe");
	v->p1pid = fork();
	if (v->p1pid == -1)
		error_message("Error creating child process");
	if (v->p1pid != 0)
	{
		ft_command_path(v, argv[2]);
		ft_command1(v, argv);
	}
	else
		ft_pipex_25line(v, argv);
}

int	main(int argc, char **argv, char *envp[])
{
	t_vars	v;

	if (argc < 5)
		error_message("error in argument");
	v.paths = ft_all_paths(envp);
	ft_pipex(&v, argv);
	return (0);
}
