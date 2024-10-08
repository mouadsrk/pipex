/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:43:27 by mserrouk          #+#    #+#             */
/*   Updated: 2023/02/11 16:23:43 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<stdio.h>
# include<stdlib.h>
# include<fcntl.h>
# include<unistd.h>
# include<sys/wait.h>
# define BUFFER_SIZE 42

typedef struct var_s
{
	char	**paths;
	char	*cmdpath;
	char	**cmd1;
	int		fd[2];
	pid_t	p1pid;
	pid_t	p2pid;
}t_vars;

void	error_message(char *str);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_command1(t_vars *v, char **argv);
void	ft_command2(t_vars *v, char **argv);
void	ft_free(char **arr, int r);
int		ft_word(char const	*s, char c);

#endif
