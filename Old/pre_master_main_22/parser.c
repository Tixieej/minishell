/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/29 13:04:11 by rde-vrie      ########   odam.nl         */
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
		if (*cur_lst->content == '$')
			expansions(cur_lst, *env);
		if (*cur_lst->content == ';')
		{
			//print_cur_struct(*cur_struct); // weg !!
			check_type(env, *cur_struct);//je hebt hier de command voor de ; verwerkt en uitgevoerd
			//print_cur_struct(*cur_struct); // deze is nog hetzelfde als voor check_type
			//write(2, "\t\tterug\n", 8);
			command = ft_clear_linked_struct(command); // hier haal je het command leeg?
			cur_struct = &command; // dus hier is cur struct ook leeg????
			cur_lst = cur_lst->next; //hier is cur_list == NULL
			//write(2, "\t\tniks\n", 7);
			if (cur_lst == NULL)
				break ;
			ft_struct_push_back(&command, (char *)cur_lst->content);// hier gaat het mis, want cur_lst->content bestaat niet
			//write(2, "\t\thoi\n", 6);
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
	ft_struct_push_back(&command, (char *)cur_lst->content);
	command->not_found = error;
	cur_lst = cur_lst->next;
	parser_part_two(cur_struct, cur_lst, env, command);
	//write(2, "\t\tna2\n", 6);
	//printf("\tcmd: [%s] - - arg0: [%s]\n", command->program, command->args->content);
	cur_lst = *list;
	if (command->pipe_check > 0)
		cur_struct = &command;
	//write(2, "\t\tparse1\n", 9);
	check_type(env, *cur_struct);// nu gaat ie hier in met struct= ?
	cur_struct = &command;
	//print_cur_struct(command); // weg !!
	if (command->not_found != 0)
		error = command->not_found;
	command = ft_clear_linked_struct(command);
	return (error);
}
