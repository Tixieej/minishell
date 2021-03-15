/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup_redirection.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:01:23 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/15 16:52:45 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include "minishell.h"

extern int errno;

int		out_redirect(t_command *cmd)
{
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	if (errno != 0)
		perror("minishell");
	if (cmd->fd_out != 1)
	{
		if (stdout_fd < 0)
			dprintf(2, "bouw hier error in!\n");
		if(dup2(cmd->fd_out, STDOUT_FILENO) < 0)
		{
			dprintf(2, "Unable to duplicate file descriptor.\n");
			exit(EXIT_FAILURE);
		}
	}
	return (stdout_fd);
}

int		in_redirect(t_command *cmd)
{
	int		stdin_fd;
	
	stdin_fd = dup(STDIN_FILENO);
	//stdin_fd = dup(-2);
	//fprintf(stderr, "value of errno: %d\n", errno);
	if (errno != 0)
		perror("minishell");
	if (cmd->fd_in != 0)
	{
		if (stdin_fd < 0)
			dprintf(2, "bouw hier error in!\n");
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
		{
			dprintf(2, "Unable to duplicate file descriptor.\n");
			exit(EXIT_FAILURE);
		}
	}
	return (stdin_fd);
}
