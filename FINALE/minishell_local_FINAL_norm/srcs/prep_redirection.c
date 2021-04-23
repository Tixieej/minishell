/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prep_redirection.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/23 20:38:22 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/23 20:43:50 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prep_in_red(t_list **cur_lst, t_command **cur_struct)
{
	ft_list_push_back(&(*cur_struct)->out_red,
		ft_strdup((*cur_lst)->content));
	if ((*cur_lst)->next)
		(*cur_lst) = (*cur_lst)->next;
	else
		error_handler("syntax error near unexpected token `newline'\n",
			*cur_lst, *cur_struct, 258);
	if (*cur_lst)
		ft_list_push_back(&(*cur_struct)->out_red,
			ft_strdup((*cur_lst)->content));
}

void	prep_out_red(t_list **cur_lst, t_command **cur_struct)
{
	ft_list_push_back(&(*cur_struct)->in_red,
		ft_strdup((*cur_lst)->content));
	if ((*cur_lst)->next)
		(*cur_lst) = (*cur_lst)->next;
	else
		error_handler("syntax error near unexpected token `newline'\n",
			*cur_lst, *cur_struct, 258);
	if (*cur_lst)
		ft_list_push_back(&(*cur_struct)->in_red,
			ft_strdup((*cur_lst)->content));
}
