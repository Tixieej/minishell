/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   external.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rdvrie <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/16 14:59:09 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(char *path, t_command *cmd, t_list *arglist, char **env)
{
	char	**args;

	args = list_to_array(arglist);
	if (execve(path, args, env) == -1)
	{
		command_not_found(cmd, cmd->program, "is a directory", 126);
		free_array(args);
		exit(126);
	}
}

void	ft_exec(char *path, t_command *cmd, char **env, pid_t process)
{
	t_list	*arglist;
	t_list	*new_elem;

	arglist = cmd->args;
	new_elem = ft_create_elem(path);
	if (!new_elem)
		error_handler("malloc failed", NULL, cmd);
	ft_lstadd_front(&arglist, new_elem);
	if (process == -1)
		process = fork();
	if (process == 0)
		child(path, cmd, arglist, env);
	else
		wait(NULL);
	free(new_elem);
}

static void	dup_back(t_command *cmd, int stdout_fd, int stdin_fd)
{
	if (cmd->out_red)
	{
		if (dup2(stdout_fd, STDOUT_FILENO) < 0)
		{
			dprintf(2, "Unable to duplicate file descriptor.\n");
			exit(9);
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

void	external(t_command *cmd, char **env, pid_t process)
{
	int		stdout_fd;
	int		stdin_fd;

	stdout_fd = out_redirect(cmd);
	stdin_fd = in_redirect(cmd);
	if (stdin_fd < 0 || stdout_fd < 0)
		return ;
	if (ft_strchr(cmd->program, '/') != 0)
		with_path(cmd, env, process);
	else
		without_path(cmd, env, process);
	dup_back(cmd, stdout_fd, stdin_fd);
}
