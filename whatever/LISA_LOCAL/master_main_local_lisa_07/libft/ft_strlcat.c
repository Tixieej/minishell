/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 09:57:07 by livlamin      #+#    #+#                 */
/*   Updated: 2019/12/03 13:31:11 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t destsize)
{
	size_t dstlen;
	size_t srclen;
	size_t i;
	size_t j;

	srclen = ft_strlen(src);
	if (destsize == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	j = dstlen;
	i = 0;
	if (destsize <= dstlen)
		return (destsize + srclen);
	while (j < destsize - 1 && src[i] != '\0')
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (dstlen + srclen);
}
