/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 09:01:25 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/20 17:11:46 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*space;

	len = ft_strlen(s1);
	space = (char *)malloc(sizeof(char) * len + 1);
	if (!space)
	{
		write(2, "minishell: malloc failed\n", 25);
		exit(1);
	}
	space[len] = '\0';
	len = 0;
	while (s1[len] != '\0')
	{
		space[len] = s1[len];
		len++;
	}
	return (space);
}
