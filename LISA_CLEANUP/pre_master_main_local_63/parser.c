/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/22 12:21:09 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_pipe(t_list **cur_lst, t_command **cur_struct)
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

static void	add_redirection(t_list **cur_lst, t_command **cur_struct)
{
	if (*(*cur_lst)->content == '>')
	{
		ft_list_push_back(&(*cur_struct)->out_red,
			ft_strdup((*cur_lst)->content));
		(*cur_lst) = (*cur_lst)->next;
		if (*cur_lst)
			ft_list_push_back(&(*cur_struct)->out_red,
				ft_strdup((*cur_lst)->content));
	}
	if (*(*cur_lst)->content == '<')
	{
		ft_list_push_back(&(*cur_struct)->in_red,
			ft_strdup((*cur_lst)->content));
		(*cur_lst) = (*cur_lst)->next;
		if (*cur_lst)
			ft_list_push_back(&(*cur_struct)->in_red,
				ft_strdup((*cur_lst)->content));
	}
}

static void	expansions(t_list *cur_lst, char **env)
{
	int		count;
	int		len;
	char	*temp;

	count = 0;
	temp = NULL;
	len = ft_strlen(cur_lst->content) - 1;
	if (cur_lst->content[0] == '$' && cur_lst->content[1] == '?')
		return ;
	while (env[count])
	{
		if (ft_strncmp(env[count], &cur_lst->content[1], len) == 0)
		{
			temp = ft_strdup(&cur_lst->content[1]);
			free(cur_lst->content);
			cur_lst->content = ft_strdup(&env[count][len + 1]);
			free(temp);
		}
		count++;
	}
}

void	parser_part_two(t_command **cur_struct, t_list *cur_lst,
			char ***env, t_command *command)
{
	while (cur_lst)
	{
		printf("cur: [%s]\n", cur_lst->content);
		if (*cur_lst->content == '$')
			expansions(cur_lst, *env);
		// prinf*cur_lst->content);
		if (*cur_lst->content == ';')
		{
			printf("Ja");
			// print_cur_struct(command); // weg !!
			check_type(env, *cur_struct);
			command = ft_clear_linked_struct(command);
			cur_struct = &command;
			cur_lst = cur_lst->next;
			ft_struct_push_back(&command, (char *)cur_lst->content);
		}
		else if (*cur_lst->content == '|')
		{
			command->pipe_check++;
			add_pipe(&cur_lst, cur_struct);
			cur_struct = &(*cur_struct)->next;
		}
		else if (*cur_lst->content == '>' || *cur_lst->content == '<')
			add_redirection(&cur_lst, cur_struct);
		else
			ft_list_push_back(&(*cur_struct)->args,
				ft_strdup((char *)(*cur_lst).content));
		cur_lst = cur_lst->next;
	}
}

int	parser(t_list **list, char ***env, t_command *command, int error)
{
	t_list		*cur_lst;
	t_command	**cur_struct;

	cur_lst = *list;
	cur_struct = &command;
	printf("cur: [%s]\n", cur_lst->content);
	ft_struct_push_back(&command, (char *)cur_lst->content);
	command->not_found = error;
	cur_lst = cur_lst->next;
	parser_part_two(cur_struct, cur_lst, env, command);
	cur_lst = *list;
	if (command->pipe_check > 0)
		cur_struct = &command;
	check_type(env, *cur_struct);
	cur_struct = &command;
	print_cur_struct(command); // weg !!
	if (command->not_found != 0)
		error = command->not_found;
	command = ft_clear_linked_struct(command);
	return (error);
}
