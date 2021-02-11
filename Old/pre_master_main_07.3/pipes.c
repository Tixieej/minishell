/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:20:04 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/03 15:38:34 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		read_pipe(t_command *cmd, int in_fd)
{
	int		stdin_fd;

	stdin_fd = dup(STDOUT_FILENO);
	if (cmd->pipe_left)
	{
		if (stdin_fd < 0)
			printf("bouw hier error in!\n");
		if(dup2(in_fd, STDOUT_FILENO) < 0)
		{
			printf("Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
	}
	return (stdin_fd);// hoe moet ik deze terugzetten? dat kan pas na de uitvoer van de command...
}

static int		write_pipe(t_command *cmd, int out_fd)
{
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	if (cmd->pipe_right)
	{
		if (stdout_fd < 0)
			printf("bouw hier error in!\n");
		if(dup2(out_fd, STDOUT_FILENO) < 0)
		{
			printf("Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
	}
	return (stdout_fd);// hoe moet ik deze terugzetten? dat kan pas na de uitvoer van de command...
}

static void		close_pipes(t_command *cmd, int *fd)
{
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

pid_t			pipes(t_command *cmd)
{
	int     fd[2];
	pid_t   process;
	int		std_fd[2];

	pipe(fd);
	if ((process = fork()) == -1) // check of fork lukt
	{
		perror("fork");
		exit(1);
	}
	if (process == 0) // Child process
	{
		close_pipes(cmd, fd); //sluit uiteindes die je niet gebruikt
		std_fd[1] = write_pipe(cmd, fd[1]); //redirect write end naar fd[1]
		std_fd[0] = read_pipe(cmd, fd[0]); //redirect read end naar fd[0]
		printf("pipe child process\n");
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