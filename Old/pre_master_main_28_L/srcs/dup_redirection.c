/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup_redirection.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:01:23 by rixt          #+#    #+#                 */
/*   Updated: 2021/04/06 16:40:28 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redirect(t_command *cmd)
{
	int		stdout_fd;

	stdout_fd = 1;
	if (cmd->fd_out != 1)
	{
		//dprintf(2, "\tSTDOUT = %i\n", STDOUT_FILENO);
		stdout_fd = dup(STDOUT_FILENO);
		//dprintf(2, "\tstdout_fd = %i\n", stdout_fd);
		if (stdout_fd < 0 || dup2(cmd->fd_out, STDOUT_FILENO) < 0)
		{
			close(cmd->fd_out);
			command_not_found(cmd, cmd->program, "Bad file descriptor", 9);
			return (-1);
		}
		close(cmd->fd_out);
	}
	return (stdout_fd);
}

int	in_redirect(t_command *cmd)
{
	int		stdin_fd;

	stdin_fd = 0;
	if (cmd->fd_in != 0)
	{
		stdin_fd = dup(STDIN_FILENO);
		if (stdin_fd < 0 || dup2(cmd->fd_in, STDIN_FILENO) < 0)
		{
			close(cmd->fd_in);
			command_not_found(cmd, cmd->program, "Bad file descriptor", 9);
			return (-1);
		}
		close(cmd->fd_in);
	}
	return (stdin_fd);
}
