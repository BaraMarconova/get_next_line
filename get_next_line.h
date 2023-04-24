/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarcono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:05:41 by bmarcono          #+#    #+#             */
/*   Updated: 2023/03/20 19:12:09 by bmarcono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NETXT_LINE_H
# define GET_NETXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 9999999
#endif

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

int	    ft_strlen(char	*str);
char	*get_next_line(int fd);


#endif
