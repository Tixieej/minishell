/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 11:42:44 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/18 16:45:06 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //WEG!!!!

static int		ft_newline(t_data *data)
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

static int		ft_make_struct(t_data **data)
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

//functie hieronder is nieuw
//static void	signal_gnl(t_data *data)
//{
//	write(1, "\b\b  \b\b", 4); //overschrijf ^D
//	signal(SIGKILL, SIG_IGN); //negeer het signaal
//	printf("data->buf = [%s]\n", data->buf); //onthoud wat je schreef	
//}
//deze functie is ook nieuw
//static void	handle_sigkill(int sig)
//{
//	printf("exit %d\n", sig);
//}

static int		ft_read(t_data *data, int fd)
{
	printf("ft_read begin, start=[%zd], bytesread=[%zd]\n", data->line_start, data->bytes_read);
	if (data->line_start == data->bytes_read)
	{
		data->line_start = 0;
		ft_bzero(data->buf, BUFFER_SIZE);
		printf("hallooo?\n");
		data->bytes_read = read(fd, data->buf, BUFFER_SIZE);//
		printf("\tgelezen = [%zd]. databuf = [%s]\n", data->bytes_read, data->buf);///avr
		ft_memcpy(&data->buf[data->bytes_read], "", 1);
	}
	if (data->bytes_read == 0)//eof gelezen
	{
		printf("0 bytes read");///avr
	//	if (*(data->buf) != '\0')///avr
	//		signal_gnl(data);///avr
		if (!data->temp)
		{
			//signal(SIGKILL, handle_sigkill);///avr
			data->temp = (char *)malloc(sizeof(char) * 1);
			if (!data->temp)
				return (-1);
			ft_memcpy(data->temp, "", 1);
		}
		return (0);
	}
	printf("return 1\n");
	return (1);
}

static int		ft_scan_data(t_data *data, int fd)
{
//	if (ft_read(data, fd) == 0)///aanpassing van rixt
//		signal_gnl(data->buf);///aanp v rixt
	if (ft_read(data, fd) != 1)//
		return (ft_read(data, fd));//
	data->i = 0;
	while (data->bytes_read > (data->i + data->line_start))
	{
		printf("while\n");
		if (data->buf[data->line_start + data->i] == '\n')
			return (ft_newline(data));
		data->i++;
	}
	if (ft_strjoin_gnl(data) == -1)
		return (-1);
	data->line_start += data->i;
	return (ft_scan_data(data, fd));
}

int				get_next_line(int fd, char **line)
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
	return (return_value);//return -2 als ctrl+d
}
