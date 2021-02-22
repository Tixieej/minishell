/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:20:04 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/16 13:28:00 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_dup2(int old, int new)
{
	if (dup2(old, new) < 0)
	{
		printf("Unable to duplicate file descriptor.");
		exit(EXIT_FAILURE);
	}
}

pid_t			pipes(t_command *cmd, t_fds *backups)
{
	int     fd[2];
	pid_t   process;

	if (cmd->pipe_right == 1) // alleen pipe als rechts pipe
	{
		pipe(fd);
		cmd->pipe_in = fd[0];
		cmd->pipe_out = fd[1];
	}
	printf("\tbackups: [%d, %d]\n", cmd->pipe_in, cmd->pipe_out);
	if ((process = fork()) == -1) // check of fork lukt
	{
		perror("fork");
		exit(1);
	}
	if (process == 0) // Child process
	{
		printf("\tpipe child process\n");
		// if (cmd->pipe_right == 1 && cmd->pipe_left == 1)
		// {
		// 	ft_dup2(fd[0], STDIN_FILENO);
		// 	backups->stin = fd[0];
		// 	ft_dup2(fd[1], STDOUT_FILENO);
		// 	backups->stout = fd[1];
		// }
		if (cmd->pipe_left == 1)
		{
			printf("\tpipe on left side\n");
			close(cmd->pipe_out); // sluit schrijfkant af
			ft_dup2(STDIN_FILENO, cmd->pipe_in);
			backups->stin = fd[0];
		}
		if (cmd->pipe_right == 1)
		{
			printf("\tpipe on right side\n");
			close(cmd->pipe_in); // sluit leeskant af
			ft_dup2(STDOUT_FILENO, cmd->pipe_out);
			backups->stout = fd[1];
		}
	}
	else
	{
		/* Parent process */
		//wait(NULL); je wil niet hier wachten
		printf("\tpipe parent process\n");
		//dup2(backups->stout, STDOUT_FILENO);
		//dup2(backups->stin, STDIN_FILENO);
		//close(fd[0]);
		//close(fd[1]);
	}
	return (process);
}
