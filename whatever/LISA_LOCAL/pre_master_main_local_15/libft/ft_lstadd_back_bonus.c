/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/21 16:44:41 by livlamin      #+#    #+#                 */
/*   Updated: 2019/12/05 08:44:53 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*temp;

	temp = *lst;
	if (!temp)
		*(lst) = new;
	else
	{
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}
