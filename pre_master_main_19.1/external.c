/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   external.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rdvrie <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/15 17:18:32 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_exec(char *path, t_command *cmd, char **env, pid_t process)
{
	char	**args;
	t_list	*arglist;
	t_list	*new_elem;

	args = NULL;
	arglist = cmd->args;
	new_elem = ft_create_elem(path);
	if (!new_elem)
		error_handler("malloc failed", NULL, cmd);
	ft_lstadd_front(&arglist, new_elem);
	if (process == -1)
		process = fork();
	if (process == 0)
	{
		args = list_to_array(&arglist);
		if (execve(path, args, env) == -1)
		{
			command_not_found(cmd, cmd->program, "is a directory", 126);
			free_array(args);
			free(new_elem);
			exit(126);
		}
	}
	else
	{
		wait(NULL);
		free(new_elem);
	}
}

static void	with_path(t_command *cmd, char **env, pid_t process)
{
	struct stat		buffer;
	char			*path;

	path = cmd->program;
	if (stat(path, &buffer) == 0)
		ft_exec(path, cmd, env, process);
	else
	{
		printf("\twith_path\n");
		command_not_found(cmd, cmd->program, "No such file or directory", 127);
	}
}

static void	attach_path(t_command *cmd, char **env, pid_t process)
{
	char		**paths;
	char		*path;
	char		*semi_path;
	struct stat	buffer;
	int			i;

	paths = make_path_array(env);
	i = 0;
	if (paths == NULL)
	{
		printf("\thai attach_path\n");
		command_not_found(cmd, cmd->program, "No such file or directory", 127);
		return ;
	}
	while (paths[i])
	{
		semi_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(semi_path, cmd->program);
		free(semi_path);
		if (stat(path, &buffer) == 0)
		{
			free_array(paths);
			ft_exec(path, cmd, env, process);
			free(path);
			return ;
		}
		free(path);
		i++;
	}
	if (stat(path, &buffer) != 0)
		command_not_found(cmd, cmd->program, "command not found", 127);
	if (paths)
		free_array(paths);
}

void	external(t_command *cmd, char **env, pid_t process)
{
	int		stdout_fd;
	int		stdin_fd;

	stdout_fd = out_redirect(cmd);
	stdin_fd = in_redirect(cmd);
	if (ft_strchr(cmd->program, '/') != 0)
		with_path(cmd, env, process);
	else
		attach_path(cmd, env, process);
	if (cmd->out_red)
	{
		if (dup2(stdout_fd, STDOUT_FILENO) < 0)//
	//	if (dup2(stdout_fd, -2) < 0)
		{
			dprintf(2, "Unable to duplicate file descriptor.\n");
			exit(9);
		//	exit(EXIT_FAILURE); exiten stopt heel minishell, dus hier komt iets anders
		}
		close(cmd->fd_out);
	}
	if (cmd->in_red)
	{
		if (dup2(stdin_fd, STDIN_FILENO) < 0)
		{
			dprintf(2, "Unable to duplicate file descriptor.\n");
			exit(9);
		}
		close(cmd->fd_in);
	}
}
