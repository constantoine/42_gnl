/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:49:34 by crebert           #+#    #+#             */
/*   Updated: 2020/01/29 14:02:21 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/*
size_t	ft_strlen(char const *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strndup(const char *s1, size_t len)
{
	size_t	index;
	char	*ptr;

	if (!(ptr = malloc(sizeof(char) * (1 + len))))
		return (NULL);
	index = 0;
	while (len--)
		ptr[index++] = *s1++;
	ptr[index] = 0;
	return (ptr);
}

char	*ft_strdup(const char *s1)
{
	int		index;
	char	*ptr;

	if (!(ptr = malloc(sizeof(char) * (1 + ft_strlen(s1)))))
		return (NULL);
	index = -1;
	while (s1[++index])
		ptr[index] = s1[index];
	ptr[index] = 0;
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	char	*str;

	index = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (!(str = malloc(sizeof(char) * (1 + ft_strlen(s1) + ft_strlen(s2)))))
		return (NULL);
	while (*s1)
		str[index++] = *s1++;
	while (*s2)
		str[index++] = *s2++;
	str[index] = 0;
	return (str);
}
*/

static int	clear_cache(char **cache)
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
		if (!(tmp = ft_strdup(&((*cache)[len + 1]))))
			get_cache_delete(line);
		if (!tmp)
			return (GNL_ERROR);
		free(*cache);
		*cache = tmp;
		if ((*cache)[0] == 0)
			get_cache_delete(cache);
		return (GNL_SUCCESS);
	}
	if (!(*line = ft_strdup(*cache)))
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
		buffer[ret] = 0;
		if (!(tmp = ft_strjoin(*line, buffer)))
			return (clear_cache(cache));
		*line = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (ret == -1)
		return (clear_cache(cache));
	if (!ft_strchr(*line, '\n'))
		return (GNL_EOF);
	if (!(tmp = ft_strndup(*line, ft_strchr(*line, '\n') - *line)))
		return (clear_cache(cache));
	if (!(cache[fd] =
	ft_strdup(&((*line)[ft_strchr(*line, '\n') - *line + 1]))))
		return (clear_cache(cache));
	free(*line);
	*line = tmp;
	return (GNL_SUCCESS);
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

/*
int			main(int ac, char **av)
{
	char	*line;
	int		fd;
	int		index;
	int		ln;
	int		ret;

	index = 1;
	while (index <= ac)
	{
		ln = 0;
		fd = open(ac >= 2 ? av[index] : "42TESTERS-GNL/files/4_newlines", O_RDONLY);
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			printf("%.2d: %s\n", ln++, line);
			free(line);
		}
		index++;
	}
}
*/
