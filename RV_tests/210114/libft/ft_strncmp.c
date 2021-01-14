/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 10:31:43 by rde-vrie      #+#    #+#                 */
/*   Updated: 2021/01/11 10:33:41 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (*s2 == '\0')
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
