/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebert <crebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:42:15 by crebert           #+#    #+#             */
/*   Updated: 2019/11/19 16:56:00 by crebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

int		get_next_line(int fd, char **line)
{
	char				buffer[BUFFER_SIZE + 1];
	char				*tmp;
	int					ret;
	int					index;
	static t_list		**maillon = NULL;

	ret = 1;
	tmp = get_fd_buffer(maillon, fd);
	if (tmp && tmp[ft_strchr(tmp)] == '\n')
	{
		tmp = ft_strndup(tmp, ft_strchr(tmp), 1);
		line = &tmp;
		return (1);
	}
	while (ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
			ft_lstclear(maillon, fd);
		if (ret == -1)
			return (-1);
		buffer[ret] = '\0';
		index = ft_strchr(tmp);
		if (!index)
			tmp = ft_strjoin(tmp, buffer);
		else
		{
			tmp = ft_strjoin(tmp, ft_strndup(buffer, index, 0));
			ft_lstpushfront(maillon, fd, &buffer[index + 1]);
			break ;
		}
	}
	*line = tmp;
	if (!ret)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	int		index;
	int 	fd;
	char	**line;
	char	*str;

	argc = 0;
	line = malloc(sizeof(char *));
	fd = open(argv[1], O_RDONLY);
	while ((index = get_next_line(fd, line)))
	{
		str = *line;
		printf("%d: %s\n", index, str);
	}
}
