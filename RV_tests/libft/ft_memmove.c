/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:29:23 by rde-vrie      #+#    #+#                 */
/*   Updated: 2019/12/12 09:41:34 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*pdst;
	const char	*psrc;

	pdst = dst;
	psrc = src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (dst);
	if (src < dst && src + len > dst)
	{
		while (len > 0)
		{
			len--;
			pdst[len] = psrc[len];
		}
	}
	while (i < len)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}
