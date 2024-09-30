/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:48:59 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/28 20:27:17 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

int	find_newline(char *buffer, int *pos, int bytes_read)
{
	while (*pos < bytes_read)
	{
		if (buffer[*pos] == '\n')
			return (1);
		(*pos)++;
	}
	return (0);
}

char	*allocate_line(int length)
{
	char	*line;

	line = malloc(sizeof(char) * (length + 1));
	if (line)
		line[length] = '\0';
	return (line);
}

int	fill_line(char *line, t_gnl *gnl, int line_len)
{
	int	i;
	int	copy_len;

	i = 0;
	while (i < line_len)
	{
		if (gnl->buf_pos >= gnl->bytes_read)
		{
			gnl->bytes_read = read(gnl->fd, gnl->buffer, BUFFER_SIZE);
			if (gnl->bytes_read <= 0)
				break ;
			gnl->buf_pos = 0;
		}
		if (gnl->bytes_read - gnl->buf_pos < line_len - i)
			copy_len = gnl->bytes_read - gnl->buf_pos;
		else
			copy_len = line_len - i;
		ft_memcpy(line + i, gnl->buffer + gnl->buf_pos, copy_len);
		i += copy_len;
		gnl->buf_pos += copy_len;
	}
	return (i);
}
