/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:20:04 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/15 13:02:27 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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


pid_t	pipes(t_command *cmd)
{
    int     fd[2]; //malloc?
	int		fd_oldin;
	int		fd_oldout;
	//fd[0] = read
	//fd[1] = write
    pid_t   process;
	fd_oldin = cmd->fd_in;
	fd_oldout = cmd->fd_in;
	// printf("oldin%d\n", fd_oldin);
	// printf("oldout%d\n", fd_oldout);
    if (pipe(fd) == -1)
		error_handler("pipe failed", NULL, cmd);
	if ((process = fork()) == -1) // check of fork lukt
    {
		perror("fork");
		error_handler("fork failed", NULL, cmd);
    	exit(1);
    }
    if (process == 0)  //CHILD
    {
		if (cmd->pipe_right == 1)
		{
			printf("JA");
			close(fd[1]);  // Close writing end of first pipe
			// fd_in = open((const char *)cmd->args, O_RDONLY, 0644);
			if (dup2(STDIN_FILENO, fd[0]) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
    		{
	    		error_handler("Unable to duplicate file descriptor.", NULL, cmd);
	    		// exit(EXIT_FAILURE); // regelen
    		}		
			// read(fd[0], cmd->args->content, ft_strlen(cmd->args->content));
			close(fd[0]);
		}
		if (cmd->pipe_left == 1)
		{
			close(fd[0]); 
			if (dup2(cmd->fd_out, fd[1]) < 0)
				return (-1);
        	// write(fd[1], cmd->args->content, ft_strlen(cmd->args->content)+1); 
			close(fd[1]);
		}
		cmd = cmd->next;
        /* Child process closes up input side of pipe */
		
    }
    else   //PARENT
    {

        /* Parent process closes up output side of pipe */
        close(fd[1]);
    }
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




        