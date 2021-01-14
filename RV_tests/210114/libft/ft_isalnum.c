/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 12:20:43 by rde-vrie      #+#    #+#                 */
/*   Updated: 2019/11/18 13:40:59 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	test;

	if (ft_isalpha(c) || ft_isdigit(c))
		test = 1;
	else
		test = 0;
	return (test);
}
