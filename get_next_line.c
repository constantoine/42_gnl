/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:49:34 by crebert           #+#    #+#             */
/*   Updated: 2020/01/14 16:48:13 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void	delete_cache(char **cache)
{
	if (*cache)
	{
		free(*cache);
		*cache = NULL;
	}
}

static void	free_and_replace(char **cache, int fd, char *str)
{
	if (cache[fd])
	{
		free(cache[fd]);
		cache[fd] = str;
	}
}

/*
** cache is a pointer to cache[fd] because otherwise I get weird bugs??
*/

static int	get_cache(char **cache, char **line)
{
	char	*tmp;
	size_t	len;

	len = 0;
	while ((*cache)[len] != 0 && (*cache)[len] != '\n')
		len++;
	if ((*cache)[len] == '\n')
	{
		*line = ft_strndup(*cache, len);
		tmp = ft_strdup(&((*cache)[len + 1]));
		if (!tmp || *line == NULL)
			return (GNL_ERROR);
		free(*cache);
		*cache = tmp;
		if ((*cache)[0] == 0)
			delete_cache(cache);
	}
	else
	{
		if (!(*line = ft_strdup(*cache)))
			return (GNL_ERROR);
		delete_cache(cache);
	}
	return (GNL_SUCCESS);
}

static int	get_next_line2(char **cache, int fd, char **line, int ret)
{
	if (ret == -1)
		return (GNL_ERROR);
	if (!cache[fd] && !ret)
		return (GNL_EOF);
	return (get_cache(&cache[fd], line));
}

int			get_next_line(int fd, char **line)
{
	static char	*cache[OPEN_MAX + 1];
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	int			ret;

	if (fd < 0 || !line)
		return (GNL_ERROR);
	while ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = 0;
		if (!cache[fd])
		{
			if (!(cache[fd] = ft_strdup(buffer)))
				return (GNL_ERROR);
		}
		else
		{
			if (!(tmp = ft_strjoin(cache[fd], buffer)))
				return (GNL_ERROR);
			free_and_replace(cache, fd, tmp);
		}
		if (ft_strchr(cache[fd], '\n'))
			break ;
	}
	return (get_next_line2(cache, fd, line, ret));
}
