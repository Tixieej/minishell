/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 15:11:46 by livlamin      #+#    #+#                 */
/*   Updated: 2019/11/29 12:46:02 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *us;
	unsigned char uc;

	us = (unsigned char *)s;
	uc = (unsigned char)c;
	while (n > 0)
	{
		if (*us == uc)
			return (us);
		us++;
		n--;
	}
	return (NULL);
}
