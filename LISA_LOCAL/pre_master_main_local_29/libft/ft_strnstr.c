/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 15:43:53 by livlamin      #+#    #+#                 */
/*   Updated: 2019/11/29 14:42:54 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t mem;
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	if (len == 0 || ft_strlen((char *)haystack) < ft_strlen((char*)needle))
		return (NULL);
	while (haystack[i] != '\0' && needle[j] != '\0' && len > i)
	{
		j = 0;
		if (haystack[i] == needle[j] && len > i)
			mem = i;
		while (haystack[i + j] == needle[j] && len > i + j)
		{
			if (needle[j + 1] == '\0' && len > i)
				return ((char *)&haystack[mem]);
			j++;
		}
		i++;
	}
	return (NULL);
}
