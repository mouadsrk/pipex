/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utiles2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:43:17 by mserrouk          #+#    #+#             */
/*   Updated: 2023/02/10 20:01:04 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_message(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	j = 0;
	i = 0;
	if (!haystack && !len)
		return (0);
	ptr = (char *)haystack;
	if (needle[0] == '\0')
		return (ptr);
	while (ptr[i] && needle[j] && i < len)
	{
		while (ptr[i + j] == needle[j] && needle[j] && (i + j) < len)
			j++;
		if (j != ft_strlen((char *)needle))
			j = 0;
		i++;
	}
	if (j == ft_strlen((char *)needle))
		return (ptr + i - 1);
	return (NULL);
}
