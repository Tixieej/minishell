/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_elem.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:23:04 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/09 14:55:52 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_create_elem(void *data)
{
	t_list *list;

	list = malloc(sizeof(t_list));
	if (list)
	{
		list->content = data;
		list->next = NULL;
	}
	return (list);
}
