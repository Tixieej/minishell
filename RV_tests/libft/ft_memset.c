/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 10:02:16 by rde-vrie      #+#    #+#                 */
/*   Updated: 2019/12/03 09:12:08 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*d;
	size_t			i;

	i = 0;
	d = b;
	while (i < len)
	{
		d[i] = c;
		i++;
	}
	return (b);
}
