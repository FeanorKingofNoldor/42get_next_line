/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:49:02 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/28 20:20:45 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_buffer(int fd, t_gnl *gnl, int *line_len)
{
	int	start_pos;

	*line_len = 0;
	while (1)
	{
		if (gnl->buf_pos >= gnl->bytes_read)
		{
			gnl->bytes_read = read(fd, gnl->buffer, BUFFER_SIZE);
			if (gnl->bytes_read <= 0)
				return (gnl->bytes_read);
			gnl->buf_pos = 0;
		}
		start_pos = gnl->buf_pos;
		if (find_newline(gnl->buffer, &gnl->buf_pos, gnl->bytes_read))
		{
			*line_len += gnl->buf_pos - start_pos + 1;
			return (1);
		}
		*line_len += gnl->bytes_read - start_pos;
		gnl->buf_pos = gnl->bytes_read;
	}
}

static char	*read_line(int fd, t_gnl *gnl)
{
	int		line_len;
	char	*line;
	int		read_result;

	read_result = read_buffer(fd, gnl, &line_len);
	if (read_result <= 0 && line_len == 0)
		return (NULL);
	line = allocate_line(line_len);
	if (!line)
		return (NULL);
	if (fill_line(line, gnl, line_len) < line_len)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (read_line(fd, &gnl));
}
