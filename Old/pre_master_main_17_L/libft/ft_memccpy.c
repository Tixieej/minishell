/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 12:05:27 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/08 14:24:22 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*usrc;
	unsigned char	*udst;
	unsigned char	uc;

	usrc = (unsigned char *)src;
	udst = (unsigned char *)dst;
	uc = (unsigned char)c;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (usrc[i] != uc)
		{
			udst[i] = usrc[i];
			i++;
		}
		else
		{
			udst[i] = usrc[i];
			return (&udst[i + 1]);
		}
	}
	return (NULL);
}
