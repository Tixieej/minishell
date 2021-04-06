/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup_redirection.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 12:01:23 by rixt          #+#    #+#                 */
/*   Updated: 2021/04/05 15:57:38 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redirect(t_command *cmd)
{
	int		stdout_fd;
	
	stdout_fd = 1;
	if (cmd->fd_out != 1)
	{
		dprintf(2, "\tSTDOUT = %i\n", STDOUT_FILENO);
		stdout_fd = dup(STDOUT_FILENO);//dit is de backup van stdout. hoef je niks mee te doen, behalve terugduppen aan het eind
		dprintf(2, "\tstdout_fd = %i\n", stdout_fd);
		if (stdout_fd < 0 || dup2(cmd->fd_out, STDOUT_FILENO) < 0)//file1 heeft nu fd 1
		{
			close(cmd->fd_out);
			command_not_found(cmd, cmd->program, "Bad file descriptor", 9);
			return (-1);
		}
		close(cmd->fd_out);
	}
	return (stdout_fd);// return backup van stdout
}

int	in_redirect(t_command *cmd)
{
	int		stdin_fd;

	stdin_fd = 0;
	if (cmd->fd_in != 0)
	{
		stdin_fd = dup(STDIN_FILENO);//RAAAAAAAAAGGGHHH stdin_fd is een backup voor STDIN
		if (stdin_fd < 0 || dup2(cmd->fd_in, STDIN_FILENO) < 0)// hier dup2 je, dus wtf doe je eigenlijk
		{
			close(cmd->fd_in);
			command_not_found(cmd, cmd->program, "Bad file descriptor", 9);
			return (-1);
		}
		close(cmd->fd_in);
	}
	return (stdin_fd);
	// hoe werkt dup? Wat is leven?? Is er een god? Waarom ben ik? Ik denk dus ik ben, maar denk ik eigenlijk wel? Wat als dit allemaal maar een simulatie is? Maakt dat uit als het voor mij echt voelt?  Ik wil niet meer. Help. Het lukt niet. Laat het eindigen. Liefst zonder al teveel lijden. Gewoon snel, tsjak en klaar. Dan hoef ik dit niet meer te doen.
}
