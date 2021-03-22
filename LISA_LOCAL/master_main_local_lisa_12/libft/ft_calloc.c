/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 08:08:06 by livlamin      #+#    #+#                 */
/*   Updated: 2019/11/27 09:18:56 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char *temp;

	temp = (unsigned char *)malloc(size * count);
	if (!temp)
		return (NULL);
	ft_bzero(temp, count * size);
	return ((void *)temp);
}
