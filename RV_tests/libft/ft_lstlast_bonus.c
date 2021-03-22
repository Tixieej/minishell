/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_listlast_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 09:50:26 by rde-vrie      #+#    #+#                 */
/*   Updated: 2019/12/02 11:28:03 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
