/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 11:43:03 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/11 09:54:08 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst2;
	unsigned char	*src2;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (n > 0)
	{
		*dst2 = *src2;
		dst2++;
		src2++;
		n--;
	}
	return (dst);
}

char	*ft_strdup_gnl(char *line)
{
	char		*result;
	size_t		length;

	length = ft_strlen(line);
	result = (char *)malloc(sizeof(char) * length + 1);
	if (!result)
		return (NULL);
	result[length] = '\0';
	length = 0;
	while (line[length] != '\0')
	{
		result[length] = line[length];
		length++;
	}
	return (result);
}

int	ft_strjoin_gnl(t_data *data)
{
	char	*str;
	size_t	len_temp;

	str = NULL;
	len_temp = 0;
	if (data->temp)
	{
		len_temp = ft_strlen(data->temp);
		str = ft_strdup_gnl(data->temp);
		if (!str)
			return (-1);
	}
	free(data->temp);
	data->temp = NULL;
	data->temp = (char *)malloc(sizeof(char) * (len_temp + data->i + 1));
	if (!data->temp)
		return (-1);
	if (str)
		ft_memcpy(data->temp, str, len_temp);
	ft_memcpy(data->temp + len_temp, data->buf + data->line_start, data->i);
	ft_memcpy(data->temp + len_temp + data->i, "", 1);
	free(str);
	str = NULL;
	return (0);
}
