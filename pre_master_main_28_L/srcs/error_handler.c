/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 11:04:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/02 10:52:07 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(char *error, t_list *list, t_command *command, int errno_val)
{
	errno = errno_val; // later dubbelcheck?
	write(2, "minishell: ", 11); //
	write(2, error, ft_strlen(error)); //
	if (list)
	{
		ft_lstclear(&list, free);
		list = NULL;
	}
	if (command)
		command = ft_clear_linked_struct(command);
	exit(errno_val);
}

void	command_not_found(t_command *command,
			char *message, char *error, int value)
{
	errno = value;
	command->not_found = value;
	write(2, "minishell: ", 11);
	write(2, message, ft_strlen(message));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}
