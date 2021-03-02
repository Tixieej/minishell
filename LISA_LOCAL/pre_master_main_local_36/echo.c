/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/21 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/02 11:56:31 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		echo(t_command *command)
{
	t_list      *cur_args;
	char        *s;
	int         n_check;
	
	cur_args = command->args;
	s = NULL;
	if (!command->args)
	{
		if (write(command->fd_out, "\n", 1) < 0)
        	error_handler("write function failed", NULL, command);
		return;
	}
	s = ft_strdup("");;
	n_check = !ft_strncmp(cur_args->content, "-n", 2);
	if (n_check == 1)
		cur_args = cur_args->next;
	while (cur_args)
	{
		s = ft_strjoin(s, (const char *)cur_args->content);
		s = ft_strjoin(s, " ");
		cur_args = cur_args->next;
	}
	if (ft_strlen(s) != 0 && n_check == 0)
		s[ft_strlen(s) - 1] = '\n';
    if (write(command->fd_out, s, ft_strlen(s)) < 0)
        error_handler("write function failed", NULL, command);
	free(s);
}