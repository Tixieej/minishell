/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:41:39 by livlamin      #+#    #+#                 */
/*   Updated: 2019/11/20 11:41:51 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *us1;
	unsigned char *us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*us1 == *us2 && *us1 != '\0' && n > 1)
	{
		n--;
		us1++;
		us2++;
	}
	return (*us1 - *us2);
}
