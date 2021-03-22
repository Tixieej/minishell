/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 11:42:44 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/22 19:35:47 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_newline(t_data *data)
{
	int		temp_len;
	char	*str;

	temp_len = 0;
	str = NULL;
	if (data->temp)
	{
		temp_len = ft_strlen(data->temp);
		str = ft_strdup(data->temp);
		if (!str)
			return (-1);
		free(data->temp);
		data->temp = NULL;
	}
	data->temp = (char *)malloc(sizeof(char) * (temp_len + data->i + 1));
	if (!data->temp)
		return (-1);
	ft_memcpy(data->temp, str, temp_len);
	ft_memcpy(data->temp + temp_len, data->buf + data->line_start, data->i);
	ft_memcpy((data->temp + temp_len + data->i), "", 1);
	data->line_start = data->i + data->line_start + 1;
	free(str);
	return (1);
}

static int	ft_make_struct(t_data **data)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!(*data))
		return (-1);
	(*data)->i = 0;
	(*data)->bytes_read = 0;
	(*data)->line_start = 0;
	(*data)->temp = NULL;
	return (0);
}

static int	ft_read(t_data *data, int fd)
{
	if ((ssize_t)data->line_start == data->bytes_read)
	{
		data->line_start = 0;
		ft_bzero(data->buf, BUFFER_SIZE);
		data->bytes_read = read(fd, data->buf, BUFFER_SIZE);
		ft_memcpy(&data->buf[data->bytes_read], "", 1);
	}
	if (data->bytes_read == 0)
	{
		write(1, "  \b\b", 4);
		if (data->temp)
			return (1);
		if (data->temp == '\0')
			exit(0); //exit code moet nog meegegeven worden
		if (!data->temp)
		{
			data->temp = (char *)malloc(sizeof(char) * 1);
			if (!data->temp)
				return (-1);
			ft_memcpy(data->temp, "", 1);
		}
		return (0);
	}
	return (1);
}

static int	ft_scan_data(t_data *data, int fd)
{
	if (ft_read(data, fd) != 1)
		return (ft_read(data, fd));
	data->i = 0;
	while (data->bytes_read > (data->i + data->line_start))
	{
		if (data->buf[data->line_start + data->i] == '\n')
			return (ft_newline(data));
		data->i++;
	}
	if (ft_strjoin_gnl(data) == -1)
		return (-1);
	data->line_start += data->i;
	return (ft_scan_data(data, fd));
}

int	get_next_line(int fd, char **line)
{
	int				return_value;
	static t_data	*data[FD_SETSIZE];

	if (fd < 0 || line == NULL || read(fd, 0, 0) == -1)
		return (-1);
	if (data[fd] == NULL)
		if (ft_make_struct(&data[fd]) == -1)
			return (-1);
	return_value = ft_scan_data(data[fd], fd);
	if (return_value == -1)
		return (-1);
	*line = ft_strdup(data[fd]->temp);
	if (!line)
		return (-1);
	free(data[fd]->temp);
	data[fd]->temp = NULL;
	if (return_value == 0)
	{
		free(data[fd]);
		data[fd] = NULL;
	}
	return (return_value);
}
