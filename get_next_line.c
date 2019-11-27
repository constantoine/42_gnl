/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:49:34 by crebert           #+#    #+#             */
/*   Updated: 2019/11/27 15:25:44 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

char	*ft_strndup(char const *str, int len)
{
	int		str_len;
	int		index;
	char	*cpy;

	index = 0;
	str_len = ft_strlen(str);
	if (len)
		str_len = len < str_len ? len : str_len;
	if (!(cpy = malloc(sizeof(char) * (1 + str_len))))
		return (NULL);
	while (*str && (index < str_len || len == 0))
		cpy[index++] = *str++;
	cpy[index] = 0;
	return (cpy);
}

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
	line = NULL;
	if (cache[fd])
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

char	*ft_strnjoin(char *s1, char const *s2, int len)
{
	size_t	index;
	int		lens2;
	char	*str;

	lens2 = 0;
	index = 0;
	if (!s1)
		return (ft_strndup(s2, len));
	if (!(str = malloc(sizeof(char) * (1 + ft_strlen(s1) + ft_strlen(s2)))))
		return (NULL);
	while (s1[index])
	{
		str[index] = s1[index];
		index++;
	}
	while (*s2 && (lens2++ < len - 1 || len == 0))
		str[index++] = *s2++;
	str[index] = 0;
	free(s1);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	char			buffer[BUFFER_SIZE + 1];
	char			*tmp;
	static	char	*cache[OPEN_MAX + 1];
	int				ret;
	int				index;

	ret = 1;
	tmp = get_cache(fd, cache);
	index = ft_strchr(tmp, '\n');
	if (0 <= index)
		*line = tmp;
	if (0 <= index)
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
			cache[fd] = ft_strndup(&buffer[index + 1], 0);
	}
	if (tmp)
		*line = tmp;
	if (tmp)
		return (1);
	return (ret);
}

int		main(int ac, char **av)
{
	char	*line = NULL;
	int		ret = 1;
	int		index = -1;
	int		fd = open("get_next_line.h", O_RDONLY);
	(void)ac;
	(void)av;
	while (++index < 20)
	{
		ret = get_next_line(fd, &line);
		printf("%d: %s\n", ret, line);
	}
}
