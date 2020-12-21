/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 09:06:41 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/02/20 09:06:46 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <limits.h>

int		read_till_end(int fd, char **line, char *buffer, int *ret)
{
	int pos;

	while (gnl_strchr(buffer, '\n') == -1 && *ret != 0)
	{
		*line = gnl_strjoin(*line, buffer, BUFFER_SIZE);
		if (*line == NULL)
			return (-1);
		*ret = read(fd, buffer, BUFFER_SIZE);
		if (*ret == -1)
		{
			free(*line);
			return (-1);
		}
		buffer[*ret] = '\0';
	}
	pos = gnl_strchr(buffer, '\n');
	*line = gnl_strjoin(*line, buffer, pos);
	if (*line == NULL)
		return (-1);
	return (pos);
}

void	shift_buffer(char *buffer, int n)
{
	int i;

	i = 0;
	while (n + i < BUFFER_SIZE)
	{
		buffer[i] = buffer[n + i];
		i++;
	}
	while (i < BUFFER_SIZE)
	{
		buffer[i] = '\0';
		i++;
	}
}

int		get_next_line(int fd, char **line)
{
	static char buffer[OPEN_MAX][BUFFER_SIZE + 1];
	int			ret;
	int			pos;

	if (!(line) || fd > OPEN_MAX || read(fd, NULL, 0) == -1)
		return (-1);
	ret = 1;
	if (*buffer[fd] == '\0')
	{
		ret = read(fd, buffer[fd], BUFFER_SIZE);
		if (ret == -1)
			return (-1);
	}
	*line = malloc(1);
	if (!(*line))
		return (-1);
	**line = '\0';
	pos = read_till_end(fd, line, buffer[fd], &ret);
	if (ret == -1 || *line == NULL)
		return (-1);
	shift_buffer(buffer[fd], pos + 1);
	if (ret == 0)
		return (0);
	return (1);
}
