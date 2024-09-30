/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:49:04 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/28 20:21:18 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_gnl
{
	char	buffer[BUFFER_SIZE];
	int		buf_pos;
	int		bytes_read;
	int		fd;
}	t_gnl;

char	*get_next_line(int fd);
char	*allocate_line(int length);
int		fill_line(char *line, t_gnl *gnl, int line_len);
int		find_newline(char *buffer, int *pos, int bytes_read);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif