/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   external_2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 11:34:08 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/29 13:10:28 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	with_path(t_command *cmd, char **env, pid_t process)
{
	struct stat		buffer;
	char			*path;

	path = cmd->program;
	if (stat(path, &buffer) == 0)
		ft_exec(path, cmd, env, process);
	else
		command_not_found(cmd, cmd->program, "No such file or directory", 127);
}

static void	attach_path(t_command *cmd, char **env, char **paths, pid_t process)
{
	int			i;
	char		*path;
	char		*semi_path;
	struct stat	buffer;

	i = 0;
	//write(2, "\t\tattach\n", 9);
	while (paths[i])
	{
		semi_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(semi_path, cmd->program);
		free(semi_path);
		if (stat(path, &buffer) == 0)
		{
			ft_exec(path, cmd, env, process);
			free(path);
			return ;
		}
		free(path);
		i++;
	}
	//write(2, "\t\thiero?\n", 9);
	if (stat(path, &buffer) != 0)
		command_not_found(cmd, cmd->program, "command not found", 127);
}

void	without_path(t_command *cmd, char **env, pid_t process)
{
	char		**paths;

	paths = make_path_array(env);
	if (paths == NULL)
	{
		command_not_found(cmd, cmd->program, "No such file or directory", 127);
		return ;
	}
	attach_path(cmd, env, paths, process);
	free_array(paths);
}
