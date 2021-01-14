/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:30:38 by rde-vrie      #+#    #+#                 */
/*   Updated: 2019/12/03 09:14:36 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, void *src, int c, size_t n)
{
	size_t			i;
	void			*ptr;
	unsigned char	*pdst;
	unsigned char	*psrc;

	i = 0;
	pdst = dst;
	psrc = src;
	while (i < n)
	{
		if (psrc[i] == (unsigned char)c)
		{
			pdst[i] = psrc[i];
			i++;
			ptr = &(dst[i]);
			return (ptr);
		}
		pdst[i] = psrc[i];
		i++;
		ptr = NULL;
	}
	return (ptr);
}
