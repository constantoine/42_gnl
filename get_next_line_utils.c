/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:49:11 by crebert           #+#    #+#             */
/*   Updated: 2019/11/19 16:56:46 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

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
	if (!start || !*start)
		free(start);
}

void	ft_lstpushfront(t_list **start, int fd, char *src)
{
	t_list	*elem;

	if (!start)
		start = malloc(sizeof(t_list *));
	if (!(elem = malloc(sizeof(t_list))))
		return ;
	elem->buffer = ft_strndup(src, 0, 0);
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

	if (!s)
		return (0);
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

	if (!start)
		return (NULL);
	elem = *start;
	res = NULL;
	while (elem)
	{
		if (elem->fd == fd)
		{
			printf("\nRECHERCHE\n");
			index = ft_strchr(elem->buffer);
			res = ft_strndup(elem->buffer, index, 0);
			if (!elem->buffer[index])
				ft_lstclear(start, fd);
			else
			{
				tmp = ft_strndup(&elem->buffer[index], 0, 1);
				elem->buffer = tmp;
			}
		}
		elem = elem->next;
	}
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		index;
	size_t	len1;
	size_t	len2;
	char	*str;

	index = 0;
	len1 = 0;
	len2 = 0;
	if (!s1)
		return (ft_strndup((char *)s2, 0, 0));
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	if (!(str = malloc(sizeof(char) * (1 + len1 + len2))))
		return (NULL);
	while (s1[++index])
		str[index] = s1[index];
	while (*s2)
		str[index++] = *s2++;
	str[index] = 0;
	if (s1)
		free((void *)s1);
	return (str);
}

char				*ft_strndup(char *str, size_t size, int	should_free)
{
	char	*ptr;
	size_t	index;
	size_t	len;

	index = 0;
	len = 0;
	if (size)
		len = size;
	else
		while (str[len])
			len++;
	if (!(ptr = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (index < len)
	{
		ptr[index] = str[index];
		index++;
	}
	ptr[index] = 0;
	if (should_free)
		free(str);
	return (ptr);
}
