/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:41:15 by crebert           #+#    #+#             */
/*   Updated: 2020/01/28 19:26:36 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
