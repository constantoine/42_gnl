/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:49:11 by crebert           #+#    #+#             */
/*   Updated: 2019/11/19 15:40:43 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int		ft_readline(char **str, int fd)
{
	char				buffer[BUFFER_SIZE + 1];
	char				*tmp;
	int					ret;
	int					index;
	static t_list		**maillon = NULL;

	index = -1;
	ret = 1;
	tmp = get_fd_buffer(maillon, fd);
	while (tmp && tmp[++index])
		if (tmp[index] == '\n')
			if (!tmp[index + 1])
				return (ft_strndup(tmp, index));
	while (ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
			ft_lstclear(maillon, fd);
		if (ret == -1)
			return (-1);
		buffer[ret] = '\0';
		tmp = ft_strjoin(tmp, buffer);
	}
	str = &tmp;
	if (!ret)
		return (0);
	return (1);
}

void	ft_lstclear(t_list **start, int fd)
{
	t_list	*prev;
	t_list	*elem;

	prev = NULL;
	elem = *start;
	while (elem)
	{
		if (elem->fd == fd)
		{
			if (prev)
				prev->next = elem->next;
			else
				*start = elem->next;
			free(elem->buffer);
			free(elem);
		}
		elem = elem->next;
	}
}

void	ft_lstpushfront(t_list **start, int fd, char *src)
{
	t_list	*elem;

	if (!(elem = malloc(sizeof(t_list))))
		return ;
	elem->buffer = src;
	elem->fd = fd;
	if (start && *start)
		elem->next = *start;
	else
		elem->next = NULL;
	start = &elem;
}

size_t	ft_strchr(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index] && s[index] != '\n')
		index++;
	return (index);
}

/*
** If buffer exists, will return it's content up to the end/first newline
** If it returns the full buffer, will then delete associated chained link
*/

char	*get_fd_buffer(t_list **start, int fd)
{
	t_list	*elem;
	size_t	index;
	char	*res;
	char	*tmp;

	elem = *start;
	res = NULL;
	while (elem)
	{
		if (elem->fd == fd)
		{
			index = ft_strchr(elem->buffer);
			res = ft_strndup(elem->buffer, index);
			if (!elem->buffer[index])
				ft_lstclear(start, fd);
			else
			{
				tmp = ft_strndup(&elem->buffer[index], 0);
				free(elem->buffer);
				elem->buffer = tmp;
			}
		}
		elem = elem->next;
	}
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	size_t	len1;
	size_t	len2;
	char	*str;

	index = 0;
	len1 = 0;
	len2 = 0;
	if (!s1)
		return (ft_strndup(s2, 0));
	if (!s2)
		return (ft_strndup(s1, 0));
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	if (!(str = malloc(sizeof(char) * (1 + len1 + len2))))
		return (NULL);
	while (*s1)
		str[index++] = *s1++;
	while (*s2)
		str[index++] = *s2++;
	str[index] = 0;
	return (str);
}
