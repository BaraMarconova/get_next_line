/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line 2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarcono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:09:28 by bmarcono          #+#    #+#             */
/*   Updated: 2023/03/22 19:57:43 by bmarcono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
#include "get_next_line.h"
//#define BUFFER_SIZE 999

/*int	ft_strlen(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
*/
char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if (c == 0)
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*newstr;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		newstr[i++] = s1[j++];
	}
	j = 0; 
	while (j < ft_strlen(s2))
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
//	free (s1);
	return (newstr);
}
char	*new_static_buffer(char *static_buffer)
{
//	int		i;
	int		len;
	char	*new;
	char	*tmp;

//	i = 0;
	len = 0;
/*	while (static_buffer[i] != '\n' && static_buffer[i] != '\0')
		i++;
*/
	tmp = ft_strchr(static_buffer, '\n');
	if (tmp)
	{
		len = ft_strlen(tmp + 1);
		tmp = tmp + 1;
	}
/*	while (static_buffer[i + len + 1] != '\0')
		len++;*/
	else
	{
//		free(static_buffer);
		return (NULL);
//		len = ft_strlen(static_buffer);
//		tmp = static_buffer;
	}
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	len = 0;
/*	while (static_buffer[i + len + 1] != '\0')
	{
		new[len] = static_buffer[i + len + 1];
		len++;
	}
	new[len] = '\0';

*/
	while (tmp[len] != '\0')
	{
		new[len] = tmp[len];
		len++;
	}
	new[len] = '\0';
	return (new);
}
char	*make_line(char *static_buffer)
{
	char	*line;
	int		i;

	if(!static_buffer)
		return (NULL);
	i = 0;
	while (static_buffer[i] != '\n' && static_buffer[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (static_buffer[i] != '\n' && static_buffer[i] != '\0')
	{
		line[i] = static_buffer[i];
		i++;
	}
	if ((static_buffer[i] == '\n'))
	{
		line[i] = '\n';
		i++;
	}
	if (static_buffer[i] == '\0' && i == 0)
	{
		free (line);
		line = NULL;
		return(NULL);
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
		if (ft_strchr(static_buffer,'\n') || int_read == 0)
			break ;
	}
	free (buffer);
	return (static_buffer) ;
}

char	*get_next_line(int fd)
{
	static char		*static_buffer;
	char			*line;
	char			*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	// funkce co vrati buffer s \n a presahem
	static_buffer = make_static_buffer(fd, static_buffer);
	// if (!static_buffer)
	// {
	// 	return (NULL);
	// }
	temp = static_buffer;
	//funkce co vezme static buffer a dojede do \n a vrati line
	line = make_line(static_buffer);
	if (!line)
	{	
		free(temp);
		return (NULL);
	}
	//funkce co vezme zbytek po \n a ulozi do static bufferu
	static_buffer = new_static_buffer(static_buffer);
	free (temp);
	return (line);
}

/*int	main()
{
	int		fd, i=0;
	char	*line;
	fd = open("test_file.txt",O_RDONLY);
	while (i < 5)
	{
//		printf("%d\n", i);
		line = get_next_line(fd);
		printf("%s", line);
		free (line);
	++i;
	}
	return (0);
}*/
