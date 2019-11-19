/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:56:45 by crebert           #+#    #+#             */
/*   Updated: 2019/11/18 19:18:34 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 32

typedef struct	s_list
{
	int				fd;
	char			*buffer;
	struct s_list	*next;
}				t_list;

char	*get_fd_buffer(t_list **start, int fd);
char	*ft_strndup(char *str, size_t size);
void	ft_lstclear(t_list **start);
int		ft_strchr(const char *s, int c);


#endif
