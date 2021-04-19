/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/19 14:19:37 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static 	char	*expansions(char *str, char **env, int count, int start)
{
	int len;

	len = 0;
	while (str[start + len] != '\0')
	{
		if (str[start + len] == '$')
		{
			start += len + 1;
			len = 0;
			while (str[start + len] != '\0' && str[start + len] != '$')
				len++;
			while (env[count])
			{
				if (ft_strncmp(env[count], &str[start], len) == 0
					&& env[count][len] == '=')
				{
					str = enter_expansion(str, &start, &len, env[count]);
					count = 0;
					break ;
				}
				count++;
			}
		}
		len++;
	}
	

	return (str);
}

static t_command	**add_pipe(t_list **cur_lst,
	t_command **cur_struct, t_command *command)
{
	command->pipe_check++;
	(*cur_struct)->pipe_right = 1;
	(*cur_lst) = (*cur_lst)->next;
	if (*cur_lst)
	{
		ft_struct_push_back(&(*cur_struct), (char *)(*cur_lst)->content);
		cur_struct = &(*cur_struct)->next;
		(*cur_struct)->pipe_left = 1;
		return (cur_struct);
	}
	return (&(*cur_struct)->next);
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

t_command *parser_part_two(t_command **cur_struct, t_list *cur_lst,
			char ***env, t_command *command)
{
	while (cur_lst)
	{
		if (cur_lst->content[0] == '$')
			cur_lst->content = expansions(cur_lst->content, *env, 0, 0);
		if (cur_lst->content[0] == ';' && cur_lst->content[1] != ';')
		{
			// print_cur_struct(command); // weg !!
			check_type(env, *cur_struct);
			command = ft_clear_linked_struct(command);
			cur_struct = &command;
			if (cur_lst->next)
				cur_lst = cur_lst->next;
			else
				return (NULL);
			ft_struct_push_back(&command, (char *)cur_lst->content);
		}
		else if (*cur_lst->content == '|')
			cur_struct = add_pipe(&cur_lst, cur_struct, command);
		else if (*cur_lst->content == '>' || *cur_lst->content == '<')
			add_redirection(&cur_lst, cur_struct);
		else
			ft_list_push_back(&(*cur_struct)->args,
				ft_strdup((char *)(*cur_lst).content));
		cur_lst = cur_lst->next;
	}
	return (command);
}

int	parser(t_list **list, char ***env, t_command *command, int error)
{
	t_list		*cur_lst;
	t_command	**cur_struct;
	int			check;

	check = 0;
	cur_lst = *list;
	cur_struct = &command;
	// while (cur_lst)
    // {
    //  printf("[%s]->", cur_lst->content);
    //  cur_lst = cur_lst->next;
    // }
	// cur_lst = *list;
	if (!cur_lst)
		return (error);
	ft_struct_push_back(&command, (char *)cur_lst->content);
	command->not_found = error;
	cur_lst = cur_lst->next;
	command = parser_part_two(cur_struct, cur_lst, env, command);
	cur_lst = *list;
	if (command->pipe_check > 0)
		cur_struct = &command;
	if (command)
		check_type(env, *cur_struct);
	cur_struct = &command;
	if (command) //
		print_cur_struct(command); // weg !!
	if (command->not_found != 0)
		error = command->not_found;
	if (command)
		command = ft_clear_linked_struct(command);
	return (error);
}
