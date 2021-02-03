/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:20:04 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/03 14:20:25 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	pipes(t_command *cmd)
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
		if (cmd->pipe_right != 1)
		{
			printf("no pipe on right side\n");
			close(fd[1]); // sluit schrijfkant af
		}
		if (cmd->pipe_left != 1)
		{
			printf("no pipe on left side\n");
			close(fd[0]); // sluit leeskant af
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