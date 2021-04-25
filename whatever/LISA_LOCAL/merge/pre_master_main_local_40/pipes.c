/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:20:04 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/10 10:30:34 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*ft_create_fd_array(t_command *cmd, int times, int *fd_array)
{
	int	count;

	count = 0;
	fd_array = malloc(sizeof(int) * (times * 2) + 1);
	fd_array[times * 2] = -1;
	if (!fd_array)
		error_handler("malloc failed in pipes", NULL, cmd);
	while (count < times)
	{
		if (pipe(fd_array + (count * 2)) < 0)
		{
			free(fd_array);
			error_handler("pipe failed", NULL, cmd);	
		}
		count++;
	}
	return (fd_array);
}

static void	close_fd_array(int *fd_array)
{
	int	count;

	count = 0;
	while (fd_array[count] != -1)
	{
		close(fd_array[count]);
		count++;
	}
}

static int	count_pipes(t_command *cmd)
{
	int			times;
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


// static void	link_fd_array(t_command *cur_cmd, int *fd_array, int count)
// {
// 	if (cur_cmd->pipe_right == 1 && cur_cmd->pipe_left != 1)
// 	{
// 		dup2(fd_array[count + 1], STDOUT_FILENO); //fd[1]
// 		close_fd_array(fd_array);
// 	}
// 	else if (cur_cmd->pipe_right == 1 && cur_cmd->pipe_left == 1)
// 	{
// 		dup2(fd_array[count - 2], STDIN_FILENO); //fd[0]
// 		dup2(fd_array[count + 1], STDOUT_FILENO); //fd[3]
// 		close_fd_array(fd_array);
// 	}
// 	else if (cur_cmd->pipe_left == 1 && cur_cmd->pipe_right != 1)
// 	{
// 		dup2(fd_array[count - 2], STDIN_FILENO); //fd[2]
// 		close_fd_array(fd_array);
// 	}
// }




pid_t	pipes(char **env, t_command *cmd, pid_t process, int count)
{
	t_command	*cur_cmd;
	int			times;
	int			*fd_array;

	cur_cmd = cmd;
	fd_array = NULL;
	times = count_pipes(cur_cmd);
	fd_array = ft_create_fd_array(cur_cmd, times, fd_array);
	while (cur_cmd)
	{	
		if ((process = fork()) == 0)
		{
			if (cur_cmd->pipe_right == 1 && cur_cmd->pipe_left != 1)
			{
				dup2(fd_array[count + 1], STDOUT_FILENO); //fd[1]
				close_fd_array(fd_array);
			}
			else if (cur_cmd->pipe_right == 1 && cur_cmd->pipe_left == 1)
			{
				dup2(fd_array[count - 2], STDIN_FILENO); //fd[0]
				dup2(fd_array[count + 1], STDOUT_FILENO); //fd[3]
				close_fd_array(fd_array);
			}
			else if (cur_cmd->pipe_left == 1 && cur_cmd->pipe_right != 1)
			{
				dup2(fd_array[count - 2], STDIN_FILENO); //fd[2]
				close_fd_array(fd_array);
			}
			// link_fd_array(cur_cmd, fd_array, count);
			check_type_two(env, cur_cmd, process);
			exit(0); //belangrijk voor non buildins aangezien er geen process wordt aangemaakt moet die wel gestops worden
		}
		if (process == -1)
			printf("minishell: fork: error"); //command freeen?
		cur_cmd = cur_cmd->next;
		count += 2;
	}
	close_fd_array(fd_array);
	cur_cmd = cmd;
	free(fd_array);
	while (wait(NULL) > 0)
		;
	return (process);
}
