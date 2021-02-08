/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/08 14:46:48 by livlamin      ########   odam.nl         */
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
	ft_struct_push_back(&(*cur_struct), (char *)(*cur_lst)->content);
	cur_struct = &(*cur_struct)->next;
	(*cur_struct)->pipe_left = 1;
}

static void		add_redirection(t_list **cur_lst, t_command **cur_struct)
{
	char *path;

	path = NULL;
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
			check_type(env, *cur_struct);
			cur_lst = cur_lst->next;
			add_semicolon(&cur_lst, cur_struct);
			cur_struct = &(*cur_struct)->next;
		}
		else if (*cur_lst->content == '|')
			add_pipe(&cur_lst, cur_struct);
		else if (*cur_lst->content == '>' || *cur_lst->content == '<')
			add_redirection(&cur_lst, cur_struct);
		else
		{
			// printf("%s\n", cur_lst->content);
			ft_list_push_back(&(*cur_struct)->args, (char *)(*cur_lst).content);
		}
		cur_lst = cur_lst->next;
	}
	cur_lst = *list; // weg?
	cur_struct = &command;
	print_cur_struct(command); // weg !!
	// cur_struct = &command;
	check_type(env, *cur_struct);
	command = ft_clear_linked_struct(command);
	// cur_struct = &command;
	printf("check is struct is leeg hieronder\n"); // weg
	// print_cur_struct(command); // weg !!
	// command = NULL; ?
	ft_lstclear(&(*list), free); // klopt dit?
	*list = NULL; //klopt dit?
	// ft_lstclear(&cur_lst, free);
	// ft_lstclear(&list, free);  ft_strctclear schrijven
}
