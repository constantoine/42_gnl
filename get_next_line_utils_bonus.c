/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:22:56 by crebert           #+#    #+#             */
/*   Updated: 2020/01/30 16:23:01 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	if (!s)
		return (NULL);
	while (*s && *s != c)
		s++;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strndup(const char *s1, int len)
{
	int		index;
	char	*ptr;

	if (len == -1)
		len = ft_strlen(s1);
	if (!(ptr = malloc(sizeof(char) * (1 + len))))
		return (NULL);
	index = 0;
	while (len-- && *s1)
		ptr[index++] = *s1++;
	ptr[index] = 0;
	return (ptr);
}

int		get_next_line_read_helper(int fd, char **line, char **cache)
{
	char	*tmp;

	if (!(*line))
		if (!(*line = ft_strndup("", -1)))
			return (GNL_ERROR);
	if (!(*line)[0])
		return (GNL_EOF);
	if (!ft_strchr(*line, '\n'))
		return (GNL_EOF);
	if (!(tmp = ft_strndup(*line, ft_strchr(*line, '\n') - *line)))
		return (clear_cache(cache));
	if (!(cache[fd] =
	ft_strndup(&((*line)[ft_strchr(*line, '\n') - *line + 1]), -1)))
		return (clear_cache(cache));
	free(*line);
	*line = tmp;
	return (GNL_SUCCESS);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	char	*str;

	index = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strndup(s2, -1));
	if (!s2)
		return (ft_strndup(s1, -1));
	if (!(str = malloc(sizeof(char) * (1 + ft_strlen(s1) + ft_strlen(s2)))))
		return (NULL);
	while (*s1)
		str[index++] = *s1++;
	while (*s2)
		str[index++] = *s2++;
	str[index] = 0;
	return (str);
}
