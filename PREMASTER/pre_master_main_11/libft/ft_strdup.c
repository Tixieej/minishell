/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 09:01:25 by livlamin      #+#    #+#                 */
/*   Updated: 2019/12/05 08:43:35 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*space;

	len = ft_strlen(s1);
	space = (char *)malloc(sizeof(char) * len + 1);
	if (!space)
		return (NULL);
	space[len] = '\0';
	len = 0;
	while (s1[len] != '\0')
	{
		space[len] = s1[len];
		len++;
	}
	return (space);
}
