/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup_redirection.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:01:23 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/23 10:07:02 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redirect(t_command *cmd)
{
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	if (cmd->out_red)
	{
		if (stdout_fd < 0)
			printf("bouw hier error in!\n");
		if(dup2(STDOUT_FILENO, cmd->fd_out) < 0)
		{
			printf("Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
	}
	return (stdout_fd);
}

int	in_redirect(t_command *cmd)
{
	int		stdin_fd;

	stdin_fd = dup(STDIN_FILENO);
	if (cmd->in_red)
	{
		if (stdin_fd < 0)
			printf("bouw hier error in!\n");
		if (dup2(STDIN_FILENO, cmd->fd_in) < 0)
		{
			printf("Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
	}
	return (stdin_fd);
}
