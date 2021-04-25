/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/21 15:43:16 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/08 14:24:18 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list		*temp;
	int			size;

	temp = lst;
	size = 0;
	while (temp)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}
