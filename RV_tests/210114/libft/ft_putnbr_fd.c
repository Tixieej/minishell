/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 16:01:18 by rde-vrie      #+#    #+#                 */
/*   Updated: 2019/12/02 16:52:49 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_intlen(int n)
{
	int		len;
	long	nbr;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		nbr = -(long)n;
		len++;
	}
	else
		nbr = n;
	while (nbr >= 1)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

void		ft_putnbr_fd(int n, int fd)
{
	int		len;
	char	c;
	long	nbr;

	nbr = (long)n;
	if (nbr < 0)
	{
		c = '-';
		write(fd, &c, 1);
		nbr *= -1;
	}
	len = ft_intlen(nbr);
	if (len > 1)
		ft_putnbr_fd(nbr / 10, fd);
	c = (nbr % 10) + '0';
	write(fd, &c, 1);
	len -= 1;
}
