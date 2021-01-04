/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_elem.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:23:04 by livlamin      #+#    #+#                 */
/*   Updated: 2019/08/21 21:46:14 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "ft_list.h"

t_list		*ft_create_elem(void *data)
{
	t_list *list;

	list = malloc(sizeof(t_list));
	if(list)
	{
		list->data = data;
		list->next = NULL;
	}
	return list;

}
