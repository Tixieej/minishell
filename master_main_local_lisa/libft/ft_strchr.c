/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 13:03:55 by livlamin      #+#    #+#                 */
/*   Updated: 2019/11/27 13:52:49 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *str;

	str = (char *)s;
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		else
			str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}
