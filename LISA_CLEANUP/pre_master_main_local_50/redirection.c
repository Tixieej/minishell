/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 13:16:00 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/10 12:25:07 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_red(t_command *command, t_list *begin)
{
	t_command	**cur_struct;

	begin = command->in_red;
	cur_struct = &command;
	while ((*cur_struct)->in_red)
	{
		if (!(ft_strncmp((const char *)(*cur_struct)->in_red->content, "<", 1)))
		{
			(*cur_struct)->in_red = (*cur_struct)->in_red->next;
			if ((*cur_struct)->in_red)
				command->fd_in = open((const char *)
						(*cur_struct)->in_red->content, O_RDONLY, 0644);
		}
		if (command->fd_in < 0)
		{
			printf("minishell: %s: No such file or directory\n",
				(const char *)(*cur_struct)->in_red->content);
			return (-1);
		}
		if ((*cur_struct)->in_red->next)
			close((int)(*cur_struct)->in_red);
		(*cur_struct)->in_red = (*cur_struct)->in_red->next;
	}
	command->in_red = begin;
	return (0);
}

void	set_fd(t_command **cur_struct, t_command *command)
{
	if (!(ft_strncmp((const char *)
				(*cur_struct)->out_red->content, ">>", 2)))
	{
		(*cur_struct)->out_red = (*cur_struct)->out_red->next;
		if ((*cur_struct)->out_red)
			command->fd_out = open((const char *)
					(*cur_struct)->out_red->content,
					O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else if (!(ft_strncmp((const char *)
				(*cur_struct)->out_red->content, ">", 1)))
	{
		(*cur_struct)->out_red = (*cur_struct)->out_red->next;
		if ((*cur_struct)->out_red)
			command->fd_out = open((const char *)
					(*cur_struct)->out_red->content,
					O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
}

int	out_red(t_command *command)
{
	t_command	**cur_struct;
	t_list		*begin;

	begin = command->out_red;
	cur_struct = &command;
	while ((*cur_struct)->out_red)
	{
		set_fd(cur_struct, command);
		if (command->fd_out < 0)
		{
			printf("minishell: %s: No such file or directory\n",
				(const char *)(*cur_struct)->out_red->content);
			return (-1);
		}
		if ((*cur_struct)->out_red->next)
			close((int)(*cur_struct)->out_red);
		(*cur_struct)->out_red = (*cur_struct)->out_red->next;
	}
	command->out_red = begin;
	return (0);
}

int	redirection(t_command *command)
{
	t_command	**cur_struct;

	cur_struct = &command;
	command->fd_in = STDIN_FILENO;
	command->fd_out = STDOUT_FILENO;
	if (in_red(command, NULL) == -1)
		return (-1);
	if (out_red(command) == -1)
		return (-1);
	return (0);
}
