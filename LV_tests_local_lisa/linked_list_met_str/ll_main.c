/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:37:52 by livlamin      #+#    #+#                 */
/*   Updated: 2019/08/21 21:19:17 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>

//t_list		*ft_create_elem(void *data);
//t_list		ft_list_push_back(t_list **begin_list, void *data);
int     main(void)
{
	t_list *list;

	list = ft_create_elem("HUISi");
	ft_list_push_back(&list, "HAAI");
	ft_list_push_back(&list, "HOOI");
	ft_list_push_back(&list, "HAL");
	
	while (list)
	{
		printf("%s\n", (char*)list->data);
		list = list->next;
	}
	return (0);
}
