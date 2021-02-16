/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:20:04 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/16 15:59:12 by livlamin      ########   odam.nl         */
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

static int	*ft_create_fd_array(t_command *cmd, int *fd_array)
{
	t_command	*cur_struct;
	int			times;
	int			count;

	cur_struct = cmd;
	times = 0;
	count = 0;
	while (cur_struct)
	{
		if (cur_struct->pipe_right == 1)
			times++;
		cur_struct = cur_struct->next;
	}
	cur_struct = cmd;
	fd_array = malloc(sizeof(int) * times * 2);
	while (count < times)
	{
		if (pipe(&fd_array[(count * 2)]) < 0)
		{
			error_handler("pipe failed", NULL, cmd);
			// free(pipe)
		}
		count++;
	}
	return(fd_array);
}


// static void	ft_create_fd_array(t_command *cmd, int **fd_array)
// {
// 	t_command	*cur_struct;
// 	int			times;
// 	int			count;

// 	cur_struct = cmd;
// 	times = 0;
// 	count = 0;
// 	while (cur_struct)
// 	{
// 		if (cur_struct->pipe_right == 1)
// 			times++;
// 		cur_struct = cur_struct->next;
// 	}
// 	cur_struct = cmd;
// 	*fd_array = malloc(sizeof(int) * times * 2);
// 	while (count < times)
// 	{
// 		if (pipe((*fd_array) + count * 2) < 0)
// 		{
// 			error_handler("pipe failed", NULL, cmd);
// 			return;
// 			// free((*fd_array));
// 			// return (1);
// 		}
// 		count++;
// 	}
// 	// return (0);
// 	return;
// }


// array = [0][1][0][1][0][1]
// array2 = [0][1]

pid_t	pipes(t_command *cmd)
{
	print_cur_struct(cmd); // weg !!
	// printf("PIPES");
	// return (-1);
    // int     fd[2];
	int		*fd_array;
	int		count;
	pid_t   process;
	int i;

	i = 0;
	process = -1;
	count = 0;
	(void)cmd;
	fd_array = NULL;
	// printf("HALLO");
	fd_array = ft_create_fd_array(cmd, fd_array);
	// ft_create_fd_array(cmd, &(*fd_array));
	// printf("%d\n", &fd_array);
	while (fd_array[i])
	{
		printf("%d\n", fd_array[i]);
		printf("i: %d\n", i);
		i++;
	}
	//fd[0] = read
	//fd[1] = write
	// if (pipe(cmd->fd_pipe) == -1)
	// 		error_handler("pipe failed", NULL, cmd);
	// while (cmd)
	// {
    // 	if (pipe(fd_array) == -1)
	// 		error_handler("pipe failed", NULL, cmd);
	// 	if ((process = fork()) == -1) // check of fork lukt
    // 	{
	// 		perror("fork");
	// 		error_handler("fork failed", NULL, cmd);
    // 		exit(1);
    // 	}
	// 	printf("%d", process);
	// 	if (process == 0)  //CHILD
    // 	{
	// 		if (cmd->pipe_right == 1)
	// 		{
	// 			printf("pipe right");
	// 			close(fd_array[0]);  // Close writing end of first pipe
	// 			if (dup2(fd_array[1], STDOUT_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
    // 			{
	//     			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
	//     			// exit(EXIT_FAILURE); // regelen
    // 			}		
	// 			close(fd_array[1]);
	// 		}
	// 		if (cmd->pipe_left == 1)
	// 		{
	// 			printf("pipe right");
	// 			close(fd_array[1]);  // Close writing end of first pipe
	// 			if (dup2(fd_array[0], STDIN_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
    // 			{
	//     			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
	//     			// exit(EXIT_FAILURE); // regelen
    // 			}		
	// 			close(fd_array[0]);
	// 		}
	// 		// check_type

	// 	}
	// 	cmd = cmd->next;	
    // }
    // // else   //PARENT
    // // {
    //     /* Parent process closes up output side of pipe */
	// 	close(fd_array[0]);
	// 	close(fd_array[1]);
	// 	wait(NULL);
        
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




        