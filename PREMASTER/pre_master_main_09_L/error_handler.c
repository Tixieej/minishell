/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 11:04:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/08 11:16:07 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(char *error, t_list **list, t_command *command)
{
	write(1, "minishell: ", 11);
	write(1, error, ft_strlen(error));
	(void)command;
	ft_lstclear(list, free); //checken of dit goed werkt
	// free(t_command)
	exit(0); // of moeten we ook op vork letten?
}
