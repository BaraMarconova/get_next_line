/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarcono <bmarcono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:40:35 by bmarcono          #+#    #+#             */
/*   Updated: 2023/04/30 14:40:42 by bmarcono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

char	*new_static_buffer(char *static_buffer)
{
	int		len;
	char	*new;
	char	*tmp;

	len = 0;
	tmp = ft_strchr(static_buffer, '\n');
	if (tmp)
	{
		len = ft_strlen(tmp + 1);
		tmp = tmp + 1;
	}
	else
		return (NULL);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	len = 0;
	while (tmp[len] != '\0')
	{
		new[len] = tmp[len];
		len++;
	}
	new[len] = '\0';
	return (new);
}

char	*allocate_line_buffer(char *static_buffer)
{
	char	*line;
	int		i;

	if (!static_buffer)
		return (NULL);
	i = 0;
	while (static_buffer[i] != '\n' && static_buffer[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	return (line);
}

char	*make_line(char *static_buffer)
{
	char	*line;
	int		i;

	line = allocate_line_buffer(static_buffer);
	if (!line)
		return (NULL);
	i = 0;
	while (static_buffer[i] != '\n' && static_buffer[i] != '\0')
	{
		line[i] = static_buffer[i];
		i++;
	}
	if ((static_buffer[i] == '\n'))
		line[i++] = '\n';
	if (static_buffer[i] == '\0' && i == 0)
	{
		free (line);
		line = NULL;
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}

char	*make_static_buffer(int fd, char *static_buffer)
{
	int		int_read;
	char	*buffer;
	char	*tmp;

	buffer = (char *)malloc(sizeof (int) * BUFFER_SIZE + 1);
	while (1)
	{
		int_read = read(fd, buffer, BUFFER_SIZE);
		if (int_read == -1)
			return (NULL);
		else if ((int_read == 0))
			break ;
		buffer[int_read] = '\0';
		tmp = static_buffer;
		static_buffer = ft_strjoin(static_buffer, buffer);
		free(tmp);
		if (ft_strchr(static_buffer, '\n') || int_read == 0)
			break ;
	}
	free (buffer);
	return (static_buffer);
}

char	*get_next_line(int fd)
{
	static char		*static_buffer[4096];
	char			*line;
	char			*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	static_buffer[fd] = make_static_buffer(fd, static_buffer[fd]);
	temp = static_buffer[fd];
	line = make_line(static_buffer[fd]);
	if (!line)
	{	
		free(temp);
		return (NULL);
	}
	static_buffer[fd] = new_static_buffer(static_buffer[fd]);
	free (temp);
	return (line);
}

// int	main()
// {
// 	int		fd, i=0;
// 	char	*line;
// 	fd = open("test_file.txt",O_RDONLY);
// 	while (i < 5)
// 	{
// //		printf("%d\n", i);
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free (line);
// 	++i;
// 	}
// 	return (0);
// }