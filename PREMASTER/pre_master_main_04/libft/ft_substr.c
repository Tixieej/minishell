/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 18:56:12 by livlamin      #+#    #+#                 */
/*   Updated: 2019/12/03 09:20:45 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	int		i;
	size_t	length;

	length = ft_strlen(s);
	if (start > length)
		return (ft_strdup(""));
	if (len > length - start)
		len = length - start;
	temp = (char *)malloc(sizeof(char) * len + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && len > 0)
	{
		temp[i] = s[start];
		i++;
		len--;
		start++;
	}
	temp[i] = '\0';
	return (temp);
}
