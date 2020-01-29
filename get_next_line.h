/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:16:53 by crebert           #+#    #+#             */
/*   Updated: 2020/01/29 13:21:02 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stddef.h>
# include <sys/uio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <stdlib.h>
# include <fcntl.h>

int		get_next_line(int fd, char **line);
size_t	ft_strlen(char const *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
char	*ft_strndup(const char *s1, size_t len);
char	*ft_strdup(const char *s1);
# define GNL_SUCCESS 1
# define GNL_EOF 0
# define GNL_ERROR -1

#endif
