/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/16 11:37:21 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		add_semicolon(t_list **cur_lst, t_command **cur_struct)
{
	ft_struct_push_back(&(*cur_struct), (char *)(*cur_lst)->content);
}

static void		add_pipe(t_list **cur_lst, t_command **cur_struct)
{
	(*cur_struct)->pipe_right = 1;
	(*cur_lst) = (*cur_lst)->next;
	if (*cur_lst)
	{
		ft_struct_push_back(&(*cur_struct), (char *)(*cur_lst)->content);
		cur_struct = &(*cur_struct)->next;
		(*cur_struct)->pipe_left = 1;
	}
}

static void		add_redirection(t_list **cur_lst, t_command **cur_struct)
{
	if (*(*cur_lst)->content == '>')
	{
		ft_list_push_back(&(*cur_struct)->out_red, ft_strdup((*cur_lst)->content));
		(*cur_lst) = (*cur_lst)->next;
		if (*cur_lst)
			ft_list_push_back(&(*cur_struct)->out_red, ft_strdup((*cur_lst)->content));
	}
	if (*(*cur_lst)->content == '<')
	{
		ft_list_push_back(&(*cur_struct)->in_red, ft_strdup((*cur_lst)->content));
		(*cur_lst) = (*cur_lst)->next;
		if (*cur_lst)
			ft_list_push_back(&(*cur_struct)->in_red, ft_strdup((*cur_lst)->content));
	}
}

void			parser(t_list **list, char **env, t_command *command)
{
	t_list		*cur_lst;
	t_command	**cur_struct;
	t_command	**cur_pipe_struct;

	cur_lst = *list;
	cur_struct = &command;
	cur_pipe_struct = NULL;
	ft_struct_push_back(&command, (char *)cur_lst->content);
	cur_lst = cur_lst->next;
	while (cur_lst)
	{
		if (*cur_lst->content == ';')
		{
			check_type(env, *cur_struct);
			cur_lst = cur_lst->next;
			add_semicolon(&cur_lst, cur_struct);
			cur_struct = &(*cur_struct)->next;
		}
		else if (*cur_lst->content == '|')
		{
			cur_pipe_struct = cur_struct;
			add_pipe(&cur_lst, cur_struct);
			cur_struct = &(*cur_struct)->next;
		}
		else if (*cur_lst->content == '>' || *cur_lst->content == '<')
			add_redirection(&cur_lst, cur_struct);
		else
			ft_list_push_back(&(*cur_struct)->args, ft_strdup((char *)(*cur_lst).content));
		cur_lst = cur_lst->next;
	}
	cur_lst = *list; // weg?
	// print_cur_struct(command); // weg !!
	if (cur_pipe_struct != NULL)
		cur_struct = cur_pipe_struct;
	check_type(env, *cur_struct);
	cur_struct = &command;
	command = ft_clear_linked_struct(command);  //werkt met exec
}

