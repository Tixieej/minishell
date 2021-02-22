/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/22 13:03:28 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/22 13:06:55 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*ft_create_fd_array(int times, int *fd_array)
{
	int			count;

	count = 0;
	fd_array = malloc(sizeof(int) * (times * 2));
	if (!fd_array)
		printf("error");
		// error_handler("malloc failed in pipes", NULL, cmd);
	while (count < times)
	{
		if (pipe(fd_array + (count * 2)) < 0)
		{
			printf("error");
			// error_handler("pipe failed", NULL, cmd);
			// free(pipe)
		}
		count++;
	}
	return (fd_array);
}

static void close_fd_array(int  *fd_array)
{
	int count;

	count = 0;
	while (fd_array[count] != '\0')
	{
		printf("fd[%d]\n", fd_array[count]);
		close(fd_array[count]);
		count++;
	}
}

static int count_pipes(t_command *cmd)
{
    int times;

    times = 1;
    while (cur_struct)
	{
		if (cur_struct->pipe_right == 1)
			times++;
		cur_struct = cur_struct->next;
	}
	cur_struct = cmd;
    return (times);
}

pid_t	pipes(char **env, t_command *cmd)
{
	int		status;
	int		i; //
	int		times;
	int		*fd_array;
	pid_t   process;
	int		count; //

	count = 0; //
	process = 1;
	(void)cmd;
	fd_array = NULL;
	times = count_pipes(cmd);
	fd_array = ft_create_fd_array(times, fd_array);
	// while (cmd)
	// {
	// 	process = fork();
	// 	if (process == -1) // check of fork lukt
    // 	{
	// 		perror("fork");
	// 		error_handler("fork failed", NULL, cmd);
    // 		exit(1);
    // 	}
	// 	printf("process %d\n", process);
		
	// 	if (process == 0)  //CHILD
    // 	{
	// 		if (cmd->pipe_right == 1 && cmd->pipe_left == 1)
	// 		{
	// 			printf("pipe_left & pipe_right\n");
	// 			if (dup2(fd_array[count], STDIN_FILENO) < 0 || dup2(fd_array[count + 1], STDOUT_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
    // 			{
	//     			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
	//     			// exit(EXIT_FAILURE); // regelen
	// 			}
	// 		}
	// 		else if (cmd->pipe_right == 1)
	// 		{
	// 			printf("pipe_right\n");
	// 			close(fd_array[count]);  // Close writing end of first pipe
	// 			if (dup2(fd_array[count + 1], STDOUT_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
    // 			{
	//     			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
	//     			// exit(EXIT_FAILURE); // regelen
	// 			}
	// 			close(fd_array[count + 1]);
	// 		}
	// 		else if (cmd->pipe_left == 1)
	// 		{
	// 			printf("pipe_left\n");
	// 			close(fd_array[count + 1]);  // Close writing end of first pipe
	// 			if (dup2(fd_array[count], STDIN_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
    // 			{
	//     			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
	//     			// exit(EXIT_FAILURE); // regelen
    // 			}	
	// 			close(fd_array[count]);
	// 		}
	// 		check_type_two(env, cmd, process);
	// 	}
	// 	count += 2;
	// 	cmd = cmd->next;	
    // }
	//  /* Parent process closes up output side of pipe */
	// close(fd_array[count]);
	// close(fd_array[count + 1]);
	// // close(fd_array[0]);
	// // close(fd_array[1]);
	// wait(NULL);
	return (process);
}


// #include "minishell.h"

// static int	*ft_create_fd_array(t_command *cmd, int *fd_array)
// {
// 	t_command	*cur_struct;
// 	int			times;
// 	int			count;

// 	cur_struct = cmd;
// 	times = 1;
// 	count = 0;
// 	while (cur_struct)
// 	{
// 		if (cur_struct->pipe_right == 1)
// 			times++;
// 		cur_struct = cur_struct->next;
// 	}
// 	cur_struct = cmd;
// 	fd_array = malloc(sizeof(int) * (times * 2));
// 	if (!fd_array)
// 		error_handler("malloc failed in pipes", NULL, cmd);
// 	while (count < times)
// 	{
// 		if (pipe(fd_array + (count * 2)) < 0)
// 		{
// 			error_handler("pipe failed", NULL, cmd);
// 			// free(pipe)
// 		}
// 		count++;
// 	}
// 	return(fd_array);
// }

// pid_t	pipes(char **env, t_command *cmd)
// {
	
// 	int		*fd_array;
// 	pid_t   process;
// 	int count; //

// 	count = 0; //
// 	process = 1;
// 	(void)cmd;
// 	fd_array = NULL;
// 	fd_array = ft_create_fd_array(cmd, fd_array);
// 	// while (fd_array[count]) //
// 	// {
// 	// 	printf("FD 0: [%d]\n", fd_array[count]);
// 	// 	printf("FD 1: [%d]\n", fd_array[count + 1]);
// 	// 	count += 2;
// 	// }
// 	//fd[0] = read
// 	//fd[1] = write
// 	// if (pipe(cmd->fd_pipe) == -1)
// 	// 		error_handler("pipe failed", NULL, cmd);
// 	// [0][1] [0][1]
// 	while (cmd)
// 	{
// 		process = fork();
// 		if (process == -1) // check of fork lukt
//     	{
// 			perror("fork");
// 			error_handler("fork failed", NULL, cmd);
//     		exit(1);
//     	}
// 		printf("process %d\n", process);
		
// 		if (process == 0)  //CHILD
//     	{
// 			if (cmd->pipe_right == 1 && cmd->pipe_left == 1)
// 			{
// 				printf("pipe_left & pipe_right\n");
// 				if (dup2(fd_array[count], STDIN_FILENO) < 0 || dup2(fd_array[count + 1], STDOUT_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
//     			{
// 	    			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
// 	    			// exit(EXIT_FAILURE); // regelen
// 				}
// 			}
// 			else if (cmd->pipe_right == 1)
// 			{
// 				printf("pipe_right\n");
// 				close(fd_array[count]);  // Close writing end of first pipe
// 				if (dup2(fd_array[count + 1], STDOUT_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
//     			{
// 	    			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
// 	    			// exit(EXIT_FAILURE); // regelen
// 				}
// 				close(fd_array[count + 1]);
// 			}
// 			else if (cmd->pipe_left == 1)
// 			{
// 				printf("pipe_left\n");
// 				close(fd_array[count + 1]);  // Close writing end of first pipe
// 				if (dup2(fd_array[count], STDIN_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
//     			{
// 	    			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
// 	    			// exit(EXIT_FAILURE); // regelen
//     			}	
// 				close(fd_array[count]);
// 			}
// 			check_type_two(env, cmd, process);
// 		}
// 		count += 2;
// 		cmd = cmd->next;	
//     }
// 	 /* Parent process closes up output side of pipe */
// 	close(fd_array[count]);
// 	close(fd_array[count + 1]);
// 	// close(fd_array[0]);
// 	// close(fd_array[1]);
// 	wait(NULL);
// 	return (process);
// }

	// while (cmd)
	// {
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




        