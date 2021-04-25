/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:20:04 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/22 19:18:25 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	*ft_create_fd_array(t_command *cmd, int *fd_array)
{
	int	count;
	int	times;

	times = count_pipes(cmd);
	count = 0;
	fd_array = malloc(sizeof(int) * (times * 2) + 1);
	fd_array[times * 2] = -1;
	if (!fd_array)
		error_handler("malloc failed in pipes", NULL, cmd, 1);
	while (count < times)
	{
		if (pipe(fd_array + (count * 2)) < 0)
		{
			free(fd_array);
			error_handler("pipe failed", NULL, cmd, 1);
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
	free(fd_array);
	fd_array = NULL;
}

static void	link_fd_array(t_command *cur_cmd, int *fd_array, int count)
{
	if (cur_cmd->pipe_right == 1 && cur_cmd->pipe_left != 1)
	{
		dup2(fd_array[count + 1], STDOUT_FILENO);
		close_fd_array(fd_array);
	}
	else if (cur_cmd->pipe_right == 1 && cur_cmd->pipe_left == 1)
	{
		dup2(fd_array[count - 2], STDIN_FILENO);
		dup2(fd_array[count + 1], STDOUT_FILENO);
		close_fd_array(fd_array);
	}
	else if (cur_cmd->pipe_left == 1 && cur_cmd->pipe_right != 1)
	{
		dup2(fd_array[count - 2], STDIN_FILENO);
		close_fd_array(fd_array);
	}
}

pid_t	pipes(char ***env, t_command *cmd, pid_t process, int count)
{
	t_command	*cur_cmd;
	int			*fd_array;

	cur_cmd = cmd;
	fd_array = NULL;
	fd_array = ft_create_fd_array(cur_cmd, fd_array);
	while (cur_cmd)
	{	
		process = fork();
		if (process == 0)
		{
			link_fd_array(cur_cmd, fd_array, count);
			check_type_two(env, cur_cmd, process);
			exit(0);
		}
		if (process == -1)
			printf("minishell: fork: error");
		cur_cmd = cur_cmd->next;
		count += 2;
	}
	close_fd_array(fd_array);
	cur_cmd = cmd;
	while (wait(NULL) > 0)
		;
	return (process);
}
