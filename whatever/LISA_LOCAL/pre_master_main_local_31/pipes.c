/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:20:04 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/22 13:52:58 by livlamin      ########   odam.nl         */
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
	t_command	*cur_struct;

	cur_struct = cmd;
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

	i = 0;
	status = 0;
	count = 0; //
	process = 1;
	fd_array = NULL;
	times = count_pipes(cmd);
	printf("times %d\n", times);
	fd_array = ft_create_fd_array(times, fd_array);
	while (cmd)
	{	
		if ((process = fork()) == 0)
		{
			if (cmd->pipe_right == 1 && cmd->pipe_left != 1)
			{
			// replace cat's stdout with write part of 1st pipe
				printf("r: count : %d\n", count);
				printf("r: times : %d\n", times);
				dup2(fd_array[count + 1], 1);
				close_fd_array(fd_array);
			}
			else if (cmd->pipe_right == 1 && cmd->pipe_left == 1)
			{
				// replace grep's stdin with read end of 1st pipe
				printf("r & l: count : %d\n", count);
				printf("r & l: times : %d\n", times);
				dup2(fd_array[count - 2], 0);
		 		// replace grep's stdout with write end of 2nd pipe
				dup2(fd_array[count + 1], 1);
				close_fd_array(fd_array);
			}
			else if (cmd->pipe_left == 1 && cmd->pipe_right != 1)
			{
				// replace cut's stdin with input read of 2nd pipe
				printf("l:count : %d\n", count);
				printf("l: times : %d\n", times);
				dup2(fd_array[count - 2], 0);
				close_fd_array(fd_array);
			}	
			check_type_two(env, cmd, process);
		}
		if (process == -1)
			printf("error");
		cmd = cmd->next;
		count += 2;
	}
	close_fd_array(fd_array);
	while (wait(NULL) > 0)
		;
	return (process);
}

// #include "minishell.h"

// // maaf dubbele array fd[2] aan //
// // *fd[0][1]
// // *fd[0][1]
// // etc ecv

// // pipe(fd)
// // maak voor elke pipe een childproces //


// // static void    dup_func(t_command *command)
// // {
// //     if (dup2(command->fd_out, STDOUT_FILENO) < 0)
// //     {
// // 	    printf("Unable to duplicate file descriptor.");
// // 	    exit(EXIT_FAILURE);
// //     }
// //     if (dup2(command->fd_in, STDIN_FILENO) < 0)
// //     {
// // 	    printf("Unable to duplicate file descriptor.");
// // 	    exit(EXIT_FAILURE);
// //     }
// // }

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
// 				printf("pipe_left\n");
// 				// close(fd_array[count + 1]);  // Close writing end of first pipe
// 				if (dup2(fd_array[count - 2], STDIN_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
//     			{
// 	    			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
// 	    			// exit(EXIT_FAILURE); // regelen
//     			}
// 				if (dup2(fd_array[count + 1], STDOUT_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
//     			{
// 	    			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
// 	    			// exit(EXIT_FAILURE); // regelen
//     			}
// 				close(fd_array[0]);
// 	  			close(fd_array[1]);
// 	  			close(fd_array[2]);
// 	 			close(fd_array[3]);
// 			}
// 			else if (cmd->pipe_right == 1)
// 			{
// 				printf("pipe_right\n");
// 				// close(fd_array[count]);  // Close writing end of first pipe
// 				if (dup2(fd_array[count + 1], STDOUT_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
//     			{
// 	    			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
// 	    			// exit(EXIT_FAILURE); // regelen
// 				}
// 				close(fd_array[0]);
// 	  			close(fd_array[1]);
// 	  			close(fd_array[2]);
// 	 			close(fd_array[3]);
// 				// close(fd_array[count + 1]);
// 			}
// 			else if (cmd->pipe_left == 1)
// 			{
// 				printf("pipe_left\n");
// 				// close(fd_array[count + 1]);  // Close writing end of first pipe
// 				if (dup2(fd_array[count], STDIN_FILENO) < 0) //if (dup2(fd_oldin, cmd->fd_in) < 0)
//     			{
// 	    			error_handler("Unable to duplicate file descriptor.", NULL, cmd);
// 	    			// exit(EXIT_FAILURE); // regelen
//     			}
// 				close(fd_array[0]);
// 	  			close(fd_array[1]);
// 	  			close(fd_array[2]);
// 	 			close(fd_array[3]);
// 				// close(fd_array[count]);
// 			}
// 			check_type_two(env, cmd, process);
// 		}
// 		count += 2;
// 		cmd = cmd->next;	
//     }
// 	 /* Parent process closes up output side of pipe */
// 	// close(fd_array[count - 2]);
// 	// close(fd_array[count - 1]);
// 	// close(fd_array[0]);
// 	// close(fd_array[1]);
// 	close(fd_array[0]);
// 	close(fd_array[1]);
// 	close(fd_array[2]);
// 	close(fd_array[3]);
// 	// wait(NULL);
// 	while (wait(NULL) > 0)
// 		;
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




		