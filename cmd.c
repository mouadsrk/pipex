/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:43:07 by mserrouk          #+#    #+#             */
/*   Updated: 2023/02/10 19:21:18 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_command1(t_vars *v,	char **argv)
{
	int	fdinput;

	fdinput = open(argv[1], O_RDONLY, 0777);
	if (fdinput == -1)
	{
		perror("Error opening input file");
		exit(1);
	}
	if (dup2(fdinput, STDIN_FILENO) == -1)
	{
		exit(1);
	}
	if (dup2(v->fd[1], STDOUT_FILENO) == -1)
	{
		exit(1);
	}
	close(v->fd[0]);
	close(v->fd[1]);
	close(fdinput);
	execve(v->cmdpath, v->cmd1, NULL);
}

void	ft_command2(t_vars *v, char **argv)
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Error opening input file");
		exit(1);
	}
	if (dup2(v->fd[0], STDIN_FILENO) == -1)
	{
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		exit(1);
	}
	close(v->fd[1]);
	close(fd);
	close(v->fd[0]);
	execve(v->cmdpath, v->cmd1, NULL);
}
