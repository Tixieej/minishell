/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup_redirection.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:01:23 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/25 13:43:10 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		out_redirect(t_command *cmd)
{
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	if (cmd->fd_out != 1)
	{
		if (stdout_fd < 0)
			dprintf(2, "bouw hier error in!\n");
		if(dup2(cmd->fd_out, STDOUT_FILENO) < 0)
		{
			dprintf(2, "Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
		//dprintf(2, "\tcmd red fd out = [%i]; stdout_fd = [%i] en STDOUT = [%i]\n", cmd->fd_out, stdout_fd, STDOUT_FILENO);
	}
	return (stdout_fd);
}

int		in_redirect(t_command *cmd)
{
	int		stdin_fd;
	
	stdin_fd = dup(STDIN_FILENO);
	if (cmd->fd_in != 0)
	{
		if (stdin_fd < 0)
			dprintf(2, "bouw hier error in!\n");
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
		{
			dprintf(2, "Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
	}
	return (stdin_fd);
}
