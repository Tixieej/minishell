/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 16:35:28 by livlamin      #+#    #+#                 */
/*   Updated: 2019/11/27 14:06:32 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*temp;
	char			a;
	unsigned int	i;

	i = 0;
	temp = malloc(sizeof(char) * ft_strlen((char *)s) + 1);
	if (!temp)
		return (NULL);
	while (s[i] != '\0')
	{
		a = f(i, s[i]);
		temp[i] = a;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
