/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 15:44:53 by livlamin      #+#    #+#                 */
/*   Updated: 2019/11/20 11:05:53 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst2;
	unsigned char	*src2;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	if (dst2 > src2)
	{
		while (len > 0)
		{
			dst2[len - 1] = src2[len - 1];
			len--;
		}
		return (dst);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
