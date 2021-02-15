/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:20:04 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/15 15:53:26 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// maaf dubbele array fd[2] aan //
// *fd[0][1]
// *fd[0][1]
// etc ecv

// pipe(fd)
// maak voor elke pipe een childproces //


// static void    dup_func(t_command *command)
// {
//     if (dup2(command->fd_out, STDOUT_FILENO) < 0)
//     {
// 	    printf("Unable to duplicate file descriptor.");
// 	    exit(EXIT_FAILURE);
//     }
//     if (dup2(command->fd_in, STDIN_FILENO) < 0)
//     {
// 	    printf("Unable to duplicate file descriptor.");
// 	    exit(EXIT_FAILURE);
//     }
// }

static int	**ft_create_fd_array(t_command *command, int **fd_array)
{
	t_command	*cur_struct;
	int			times;

	cur_struct = command;
	times = 0;
	while (cur_struct)
	{
		if (cur_stuct->pipe_right == 1)
			times++;
	}
	cur_struct = command;
	

}


pid_t	pipes(t_command *cmd)
{
    // int     fd[2];
	int		**fd_array;
	pid_t   process;

	process = 0;
	fd_array = ft_create_fd_array(cmd, fd_array);
	//fd[0] = read
	//fd[1] = write
	while (cmd)
	{
    	if (pipe(*fd_array) == -1)
			error_handler("pipe failed", NULL, cmd);
		if ((process = fork()) == -1) // check of fork lukt
    	{
			perror("fork");
			error_handler("fork failed", NULL, cmd);
    		exit(1);
    	}
		if (process == 0)  //CHILD
    	{
			if (cmd->pipe_right == 1 && cmd->pipe_left == 1)
			{
				if (dup2(STDOUT_FILENO, *fd_array[1]) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
    			{
	    			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
	    			// exit(EXIT_FAILURE); // regelen
    			}
				if (dup2(STDIN_FILENO, *fd_array[0]) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
    			{
	    			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
	    			// exit(EXIT_FAILURE); // regelen
    			}
			}
			}
			if (cmd->pipe_right == 1)
			{
				close(*fd_array[0]);  // Close writing end of first pipe
				if (dup2(STDOUT_FILENO, *fd_array[1]) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
    			{
	    			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
	    			// exit(EXIT_FAILURE); // regelen
    			}		
				close(*fd_array[1]);
			}
			if (cmd->pipe_left == 1)
			{
				close(*fd_array[1]);  // Close writing end of first pipe
				if (dup2(STDIN_FILENO, *fd_array[0]) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
    			{
	    			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
	    			// exit(EXIT_FAILURE); // regelen
    			}		
				close(*fd_array[0]);
			}
		}
		fd_array++;
		cmd = cmd->next;	
    }
    // else   //PARENT
    // {
        /* Parent process closes up output side of pipe */
        close(fd[0]);
		close(fd[1]);
    // }
	


	return (process);
}



// pid_t	pipes(t_command *cmd)
// {
// 	int     fd[2];
// 	pid_t   process;

// 	pipe(fd);
// 	if ((process = fork()) == -1) // check of fork lukt
// 	{
// 		perror("fork");
// 		exit(1);
// 	}
// 	if (process == 0) // Child process
// 	{
// 		printf("pipe child process\n");
// 		if (cmd->pipe_right != 1)
// 		{
// 			printf("no pipe on right side\n");
// 			close(fd[1]); // sluit schrijfkant af
// 		}
// 		if (cmd->pipe_left != 1)
// 		{
// 			printf("no pipe on left side\n");
// 			close(fd[0]); // sluit leeskant af
// 		}
// 	}
// 	else
// 	{
// 		/* Parent process */
// 		wait(NULL);
// 		printf("pipe parent process\n");
// 		//close(fd[1]);
// 	}
// 	return (process);
// }




        