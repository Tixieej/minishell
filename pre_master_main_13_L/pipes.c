/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:20:04 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/11 18:15:43 by rixt          ########   odam.nl         */
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

pid_t			pipes(t_command *cmd)
{
	int     fd[2];
	pid_t   process;

	pipe(fd);
	if ((process = fork()) == -1) // check of fork lukt
	{
		perror("fork");
		exit(1);
	}
	if (process == 0) // Child process
	{
		printf("pipe child process\n");
		if (cmd->pipe_right == 1 && cmd->pipe_left == 1)
		{
			ft_dup2(fd[0], STDIN_FILENO);
			ft_dup2(fd[1], STDOUT_FILENO);
		}
		if (cmd->pipe_right != 1)
		{
			printf("no pipe on right side\n");
			close(fd[1]); // sluit schrijfkant af
			ft_dup2(fd[0], STDIN_FILENO);
		}
		if (cmd->pipe_left != 1)
		{
			printf("no pipe on left side\n");
			close(fd[0]); // sluit leeskant af
			ft_dup2(fd[1], STDOUT_FILENO);
		}
	}
	else
	{
		/* Parent process */
		wait(NULL);
		printf("pipe parent process\n");
		//close(fd[1]);
	}
	return (process);
}
