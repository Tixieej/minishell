/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/12/01 15:55:26 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_type(t_list **list, char **env)
{
	t_list	*begin;

	begin = *list;
	while (begin)
	{
		if (ft_strncmp((const char *)begin->content, "cat", 3) == 0)
			printf("cat type\n");
		if (ft_strncmp((const char *)begin->content, "cp", 2) == 0)
			ft_parse(*list, env);
		if (ft_strncmp((const char *)begin->content, "echo", 4) == 0)
			printf("echo type\n");
		begin = begin->next;
	}
	begin = *list;
}
