/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/28 17:28:48 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		add_semicolon(t_list **cur_lst, t_command **cur_struct)
{
	(*cur_lst) = (*cur_lst)->next;
	ft_struct_push_back(&(*cur_struct), (char *)(*cur_lst)->content);
	cur_struct = &(*cur_struct)->next;
}

static void		add_pipe(t_list **cur_lst, t_command **cur_struct)
{
	(*cur_struct)->pipe_right = 1;
	(*cur_lst) = (*cur_lst)->next;
	ft_struct_push_back(&(*cur_struct), (char *)(*cur_lst)->content);
	cur_struct = &(*cur_struct)->next;
	(*cur_struct)->pipe_left = 1;
}

static void		add_redirection(t_list **cur_lst, t_command **cur_struct)
{
	if (*(*cur_lst)->content == '>')
	{
		ft_list_push_back(&((*cur_struct)->out_red), (*cur_lst)->content);
		(*cur_lst) = (*cur_lst)->next;
		ft_list_push_back(&((*cur_struct)->out_red), (*cur_lst)->content);
	}
	else if (*(*cur_lst)->content == '<')
	{
		ft_list_push_back(&((*cur_struct)->in_red), (*cur_lst)->content);
		(*cur_lst) = (*cur_lst)->next;
		if ((*cur_lst))
			ft_list_push_back(&((*cur_struct)->in_red), (*cur_lst)->content);
	}
}

void			parser(t_list **list, char **env, t_command *command)
{
	t_list		*cur_lst;
	t_command	**cur_struct;

	cur_lst = *list;
	cur_struct = &command;
	ft_struct_push_back(&command, (char *)cur_lst->content);
	cur_lst = cur_lst->next;
	while (cur_lst)
	{
		if (*cur_lst->content == ';')
		{
			check_type(list, env, *cur_struct);
			add_semicolon(&cur_lst, cur_struct);
			// doen we hier niet 2x check_type, want onder de while loop gebeurt het weer?
		}
		else if (*cur_lst->content == '|')
			add_pipe(&cur_lst, cur_struct);
		else if (*cur_lst->content == '>' || *cur_lst->content == '<')
			add_redirection(&cur_lst, cur_struct);
		else
			ft_list_push_back(&((*cur_struct)->args), cur_lst->content);
		cur_lst = cur_lst->next;
	}
	check_type(list, env, *cur_struct);
	cur_lst = *list;
	cur_struct = &command;
	// printf("go to execute function\n");
	while (*cur_struct)// loop om te lezen wat er gebeurt, later weghalen
	{
		printf("\tprogram: [%s]\n", ((char*)(*cur_struct)->program));
		while (((*cur_struct)->in_red))
		{
			printf("\tin_red: [%s]\n", ((*cur_struct)->in_red)->content);
			(*cur_struct)->in_red = (*cur_struct)->in_red->next;
		}
		while (((*cur_struct)->out_red))
		{
			printf("\tout_red: [%s]\n", ((*cur_struct)->out_red)->content);
			(*cur_struct)->out_red = (*cur_struct)->out_red->next;
		}
		while (((*cur_struct)->args))
		{
			printf("\targs: [%s]\n", ((*cur_struct)->args)->content);
			(*cur_struct)->args = (*cur_struct)->args->next;
		}
		printf("\tpipe_left: [%d]\n", ((*cur_struct)->pipe_left));
		printf("\tpipe_right: [%d]\n\n", ((*cur_struct)->pipe_right));
		cur_struct = &(*cur_struct)->next;
	}
	cur_struct = &command;
	// ft_lstclear(&cur_lst, free);
	// ft_lstclear(&list, free);  ft_strctclear schrijven
}
