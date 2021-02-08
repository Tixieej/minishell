/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_struct.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/08 12:22:48 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command		*ft_clear_linked_struct(t_command *command)
{
	t_command **cur_struct;

	cur_struct = &command;
	while(*cur_struct)
	{
		if ((*cur_struct)->program)
		{
			free((*cur_struct)->program); //fixen
			(*cur_struct)->program = NULL;
		}
		if ((*cur_struct)->args)
		{
			ft_lstclear(&(*cur_struct)->args, free);
			(*cur_struct)->args = NULL;
		}
		if ((*cur_struct)->in_red)
		{
			ft_lstclear(&(*cur_struct)->in_red, free);
			(*cur_struct)->in_red = NULL;
		}
		if ((*cur_struct)->out_red)
		{
			ft_lstclear(&(*cur_struct)->out_red, free);
			(*cur_struct)->out_red = NULL;
		}
		(*cur_struct)->pipe_left = 0;
        (*cur_struct)->pipe_right = 0;
		(*cur_struct)->fd_in = 0;
		(*cur_struct)->fd_out = 0;
		(*cur_struct)->next = NULL;
		cur_struct = &(*cur_struct)->next;
		
	}
	return (command);
}

 
t_command		*ft_create_linked_struct(char *data)
{
	t_command *command;

	command = malloc(sizeof(t_command));
	if (command)
	{
        command->program = ft_strdup(data);
		command->args = NULL;
        command->pipe_left = 0;
        command->pipe_right = 0;
		command->fd_in = 0;
		command->fd_out = 0;
		command->in_red = NULL;
		command->out_red = NULL;
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