/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:49:34 by crebert           #+#    #+#             */
/*   Updated: 2019/11/26 22:16:43 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 32
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <limits.h>

int		ft_strchr(const char *str, char c)
{
	size_t	index;

	if (!str)
		return (-1);
	index = 0;
	while (str[index])
		if (str[index++] == c)
			return (index - 1);
	return (-1);
}

char	*get_cache(int fd, char **cache)
{
	char	*line;
	char	*tmp;
	int		index;

	tmp = NULL;
	if (*cache[fd])
	{
		index = ft_strchr(cache[fd], '\n');
		if (index >= 0)
		{
			line = ft_strndup(cache[fd], index + 1);
			tmp = ft_strndup(&cache[fd][index + 1], 0);
			free(cache[fd]);
			if (*tmp)
				cache[fd] = tmp;
			return (line);
		}
		line = ft_strndup(cache[fd], 0);
		free(cache[fd]);
	}
	return (line);
}

int		get_next_line(int fd, char **line)
{
	char			buffer[BUFFER_SIZE + 1];
	char			*tmp;
	static	char	*cache[OPEN_MAX + 1];
	int				ret;
	int				index;

	ret = 1;
	index = -1;
	tmp = get_cache(fd, cache);
	if (0 <= ft_strchr(tmp, '\n'))
		*line = tmp;
	if (0 <= ft_strchr(tmp, '\n'))
		return (1);
	while (ret > 0 && index < 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		buffer[ret] = 0;
		if (ret == -1)
			return (-1);
		index = ft_strchr(buffer, '\n');
		tmp = ft_strnjoin(tmp, buffer, index + 1);
		if (index >= 0)
			cache[fd] = ft_strndup(tmp[index + 1], 0);
	}
	if (tmp)
		*line = tmp;
	if (tmp)
		return (1);
	return (ret);
}
