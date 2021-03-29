/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 11:04:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/09 11:53:06 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(char *error, t_list *list, t_command *command)
{
	write(1, "minishell: ", 11);
	write(1, error, ft_strlen(error));
	if (list)
	{
		ft_lstclear(&list, free);
		list = NULL;
	}
	if (command)
		command = ft_clear_linked_struct(command);
	exit(0);
}