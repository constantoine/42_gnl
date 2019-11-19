/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:56:45 by crebert           #+#    #+#             */
/*   Updated: 2019/11/19 16:40:49 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct		s_list
{
	int				fd;
	char			*buffer;
	struct s_list	*next;
}					t_list;

char				*get_fd_buffer(t_list **start, int fd);
char				*ft_strndup(char *str, size_t size, int	should_free);
void				ft_lstclear(t_list **start, int fd);
size_t				ft_strchr(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_lstpushfront(t_list **start, int fd, char *src);

#endif
