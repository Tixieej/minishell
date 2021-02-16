/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 11:04:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/15 11:56:29 by rixt          ########   odam.nl         */
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
		ft_clear_linked_struct(command);
	exit(0); // of moeten we ook op fork letten?
}
