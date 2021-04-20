/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup_redirection.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:01:23 by rixt          #+#    #+#                 */
/*   Updated: 2021/04/19 15:57:32 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redirect(t_command *cmd)
{
	int	stdout_fd;
	
	stdout_fd = STDOUT_FILENO;
	if (cmd->fd_out != 1)
	{
		stdout_fd = dup(STDOUT_FILENO);
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
	int	stdin_fd;

	stdin_fd = STDIN_FILENO;
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