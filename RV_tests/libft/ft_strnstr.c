/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 09:38:57 by rde-vrie      #+#    #+#                 */
/*   Updated: 2019/12/03 09:30:47 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	start;
	char	*sub;

	index = 0;
	start = 0;
	if (needle[index] == '\0')
		return ((char *)haystack);
	while (haystack[start] != '\0')
	{
		while (haystack[start + index] == needle[index])
		{
			if (start + index >= len)
				return (NULL);
			index++;
			if (needle[index] == '\0')
			{
				sub = ((char *)&(haystack[start]));
				return (sub);
			}
		}
		index = 0;
		start++;
	}
	return (NULL);
}
