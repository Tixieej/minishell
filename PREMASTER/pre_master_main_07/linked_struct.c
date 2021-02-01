/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_struct.c                                    :+:    :+:            */
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
		command->args = NULL;
        command->pipe_left = 0;
        command->pipe_right = 0;
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