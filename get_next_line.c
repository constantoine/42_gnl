/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:49:34 by crebert           #+#    #+#             */
/*   Updated: 2020/01/30 16:23:29 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			clear_cache(char **cache)
{
	unsigned int	fd;

	fd = 0;
	while (fd < OPEN_MAX + 1)
	{
		free(cache[fd]);
		cache[fd++] = NULL;
	}
	return (GNL_ERROR);
}

static int	get_cache_delete(char **cache)
{
	if (*cache)
	{
		free(*cache);
		*cache = NULL;
	}
	return (GNL_EOF);
}

static int	get_cache(char **cache, char **line)
{
	char	*tmp;
	size_t	len;

	len = 0;
	while ((*cache)[len] != 0 && (*cache)[len] != '\n')
		len++;
	if ((*cache)[len] == '\n')
	{
		if (!(*line = ft_strndup(*cache, len)))
			return (GNL_ERROR);
		if (!(tmp = ft_strndup(&((*cache)[len + 1]), -1)))
			get_cache_delete(line);
		if (!tmp)
			return (GNL_ERROR);
		free(*cache);
		*cache = tmp;
		if ((*cache)[0] == 0)
			get_cache_delete(cache);
		return (GNL_SUCCESS);
	}
	if (!(*line = ft_strndup(*cache, -1)))
		return (GNL_ERROR);
	return (get_cache_delete(cache));
}

static int	get_next_line_read(int fd, char **line, char **cache)
{
	int		ret;
	char	*tmp;
	char	buffer[BUFFER_SIZE + 1];

	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (!buffer[0])
		{
			free(*line);
			if (!(*line = ft_strndup("", -1)))
				return (clear_cache(cache));
			return (GNL_EOF);
		}
		buffer[ret] = 0;
		if (!(tmp = ft_strjoin(*line, buffer)))
			return (clear_cache(cache));
		free(*line);
		*line = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (ret == -1)
		return (clear_cache(cache));
	return (get_next_line_read_helper(fd, line, cache));
}

int			get_next_line(int fd, char **line)
{
	static char	*cache[OPEN_MAX + 1];
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (GNL_ERROR);
	*line = NULL;
	if (cache[fd])
	{
		if ((ret = get_cache(&cache[fd], line)) == GNL_ERROR)
			return (clear_cache(cache));
		if (ret == GNL_SUCCESS)
			return (GNL_SUCCESS);
	}
	return (get_next_line_read(fd, line, cache));
}
