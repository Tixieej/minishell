/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:37:52 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/21 11:25:31 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "../get_next_line.h"
#include <fcntl.h>

t_list		*ft_create_elem(void *data);
void		ft_list_push_back(t_list **begin_list, void *data);

int     main(void)
{
	char	*line;
	int		result;
	t_list *list;
	int i = 0;

	result = 1;
	//line = NULL;
	//(void)argv;
	
	while (result == 1)
	{
		result = get_next_line(0, &line);
		//ft_create_elem(line);
		ft_list_push_back(&list, line);
		//free(line);
	}

	while (list)
	{
		printf("element %i in list: [%s]\n", i, (char*)list->data);
		printf("adres naar volgende element: %p\n", list->next);
		list = list->next;
		i++;
	}
	return (0);
}
