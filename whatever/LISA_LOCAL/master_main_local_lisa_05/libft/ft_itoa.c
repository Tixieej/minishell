/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 17:55:43 by livlamin      #+#    #+#                 */
/*   Updated: 2019/11/27 09:18:56 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_times(int length)
{
	int result;

	result = 1;
	while (length > 1)
	{
		result = result * 10;
		length--;
	}
	return (result);
}

static int		ft_length(int n)
{
	int i;
	int temp;

	i = 0;
	temp = n;
	if (temp < 0)
		i = 1;
	while (temp)
	{
		temp = temp / 10;
		i++;
	}
	return (i);
}

static char		*ft_convert(int length, char *str, int n)
{
	int		x;
	long	temp;

	x = 0;
	if (str[x] == '-')
		x++;
	while (length > 0)
	{
		temp = n / ft_times(length);
		str[x] = 48 + temp;
		n = n - (ft_times(length) * temp);
		length--;
		x++;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		length;
	int		x;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	x = 0;
	length = ft_length(n);
	str = (char *)malloc(sizeof(char) * length + 1);
	if (!str)
		return (NULL);
	str[length] = '\0';
	if (n < 0)
	{
		str[x] = '-';
		n = n * -1;
		x++;
		length--;
	}
	if (length > 0)
		str = ft_convert(length, str, n);
	return (str);
}
