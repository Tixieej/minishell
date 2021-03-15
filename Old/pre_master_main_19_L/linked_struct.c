/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_struct.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/11 13:01:09 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_command	*ft_clear_linked_struct(t_command *command)
// {
// 	t_command	*first;
// 	t_list		*cur_args;
// 	t_list		*cur_in_red;
// 	t_list		*cur_out_red;
// 	t_command	*temp;

// 	first = &command;
// 	if (command->next)
// 		command = command->next;
// 	while (command)
// 	{
// 		cur_args = command->args;
// 		cur_in_red = command->in_red;
// 		cur_out_red = command->out_red;
// 		if ((command)->program)
// 			free(command->program);
// 		if (cur_args)
// 			ft_lstclear(&cur_args, free);
// 		if (cur_in_red != NULL)
// 			ft_lstclear(&cur_in_red, free);
// 		if (cur_out_red)
// 			ft_lstclear(&cur_out_red, free);
// 		temp = command;
// 		command = command->next;
// 		free(temp);
// 	}
// 	return (NULL);
// }

t_command	*ft_clear_linked_struct(t_command *command)
{
	t_list		*cur_args;
	t_list		*cur_in_red;
	t_list		*cur_out_red;
	t_command	*temp;

	while (command)
	{
		cur_args = command->args;
		cur_in_red = command->in_red;
		cur_out_red = command->out_red;
		if ((command)->program)
			free(command->program);
		if (cur_args)
			ft_lstclear(&cur_args, free);
		if (cur_in_red != NULL)
			ft_lstclear(&cur_in_red, free);
		if (cur_out_red)
			ft_lstclear(&cur_out_red, free);
		temp = command;
		command = command->next;
		free(temp);
	}
	return (NULL);
}

t_command	*ft_create_linked_struct(char *data)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	if (command)
	{
		command->program = ft_strdup(data);
		command->args = NULL;
		command->pipe_left = 0;
		command->pipe_right = 0;
		command->fd_in = 0;
		command->fd_out = 1;
		command->pipe_check = 0;
		command->not_found = 0;
		command->in_red = NULL;
		command->out_red = NULL;
		command->next = NULL;
	}
	return (command);
}

void	ft_struct_push_back(t_command **begin_list, char *data)
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
