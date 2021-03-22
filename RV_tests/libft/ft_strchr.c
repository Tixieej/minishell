/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 11:38:49 by rde-vrie      #+#    #+#                 */
/*   Updated: 2019/12/03 09:26:01 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	char	*loc;
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			i++;
		else
		{
			loc = (char *)&s[i];
			return (loc);
		}
	}
	if (c == '\0')
		loc = (char *)&s[i];
	else
		loc = NULL;
	return (loc);
}
