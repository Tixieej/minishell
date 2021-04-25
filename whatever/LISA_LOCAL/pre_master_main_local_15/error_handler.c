/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/25/01 11:04:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/28 17:51:06 by rixt          ########   odam.nl         */
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
