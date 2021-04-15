/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 14:21:36 by rde-vrie      #+#    #+#                 */
/*   Updated: 2021/04/15 13:45:03 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_list *list)
{
	t_list *cur_list;
	
	cur_list = list;
	while (cur_list)
	{
		if (ft_strchr(";|><", cur_list->content[0]))//als cur list = ;<>| en dan ;<>|  ??
		{
			if (cur_list->next && ft_strchr(";|", cur_list->next->content[0]))
			{
				//command_not_found(, cur_list->content, "syntax error near unexpected token", 258);
				write(2, "minishell: syntax error near unexpected token `", 47);
				write(2, cur_list->next->content, ft_strlen(cur_list->next->content));
				write(2, "'\n", 2);
				return (-1);
			}
		}
		cur_list = cur_list->next;
	}
	return (0);
}
