/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 09:57:19 by rde-vrie      #+#    #+#                 */
/*   Updated: 2019/12/10 11:19:41 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(const char c)
{
	if (c == ' ')
		return (1);
	if (c >= '\t' && c <= '\r')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	int		index;
	long	nb;
	int		sgn;
	long	max;

	index = 0;
	nb = 0;
	sgn = 1;
	max = 9223372036854775807;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sgn = -1;
		index++;
	}
	while (str[index] != '\0' && str[index] >= '0' && str[index] <= '9')
	{
		nb = nb * 10 + str[index] - '0';
		if (nb > (max / 10))
			return (sgn > 0) ? (-1) : (0);
		index++;
	}
	return ((int)(sgn * nb));
}
