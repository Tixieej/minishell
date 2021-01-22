/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/12/01 15:55:26 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command		*ft_create_linked_struct(char *data)
{
	t_command *command;

	command = malloc(sizeof(t_command));
	if (command)
	{
        command->program = data;
        command->args = ft_strdup("");
        command->pipe_left = 0;
        command->pipe_right = 0;
		command->redirection = 0;
		command->next = NULL;
	}
	return (command);
}

void		ft_struct_push_back(t_command **begin_list, char *data)
{
	t_command	*temp;

	temp = *begin_list;
	if (*begin_list)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = ft_create_linked_struct(data);
	}
	else
		*begin_list = ft_create_linked_struct(data);
}

void	parser(t_list **list, char **env, t_command	*command)
{
	t_list		*cur_lst;
	t_command	**cur_struct;

	cur_struct = &command;
	cur_lst = *list;
	(void)env;
	ft_struct_push_back(&(*cur_struct), (char *)cur_lst->content);
	cur_lst = cur_lst->next;
	while (cur_lst)
	{
		// if (ft_strncmp((const char *)cur_lst->content, ">", 1))
		// {
		// 	(*cur_struct)->redirection++;
		// }
		if (ft_strncmp((const char *)cur_lst->content, ";", 1) && ft_strncmp((const char *)cur_lst->content, "|", 1))
		{
			(*cur_struct)->args = ft_strjoin((*cur_struct)->args, cur_lst->content);
			(*cur_struct)->args = ft_strjoin((*cur_struct)->args, " "); //tijdelijk om woorden iig los te lezen
		}
		if (ft_strncmp((const char *)cur_lst->content, ";", 1) == 0)
		{
			check_type(list, env, *cur_struct);
			cur_lst = cur_lst->next;
			ft_struct_push_back(&(*cur_struct), (char *)cur_lst->content);
			cur_struct = &(*cur_struct)->next;
		}	
		if (ft_strncmp((const char *)cur_lst->content, "|", 1) == 0)
		{
			(*cur_struct)->pipe_right = 1;
			cur_lst = cur_lst->next;
			ft_struct_push_back(&(*cur_struct), (char *)cur_lst->content);
			cur_struct = &(*cur_struct)->next;
			(*cur_struct)->pipe_left = 1;
		}
		cur_lst = cur_lst->next;
	}
	check_type(list, env, *cur_struct);
	cur_lst = *list;
	cur_struct = &command;
	
	// printf("go to execute function\n");
	while (*cur_struct)// loop om te lezen wat er gebeurd later weghalen
	{
			printf("program: [%s]\n", ((char*)(*cur_struct)->program));
			printf("args: [%s]\n", ((char*)(*cur_struct)->args));
			printf("pipe_left: [%d]\n", ((*cur_struct)->pipe_left));
			printf("pipe_right: [%d]\n", ((*cur_struct)->pipe_right));
			printf("redirection: [%d]\n", ((*cur_struct)->redirection));
			// printf("begin adress: %p\n", begin);
			cur_struct = &(*cur_struct)->next;
	}
	cur_struct = &command;
	// ft_lstclear(&cur_lst, free);
	// ft_lstclear(&list, free);  ft_strctclear schrijven
}
