/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 09:38:49 by livlamin      #+#    #+#                 */
/*   Updated: 2019/11/27 09:18:56 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	temp = (char *)malloc(sizeof(char) * len + 1);
	if (!temp)
		return (NULL);
	temp[len] = '\0';
	len = 0;
	while ((char)s1[len] != '\0')
	{
		temp[len] = (char)s1[len];
		len++;
	}
	while ((char)s2[i] != '\0')
	{
		temp[len] = (char)s2[i];
		i++;
		len++;
	}
	return (temp);
}
