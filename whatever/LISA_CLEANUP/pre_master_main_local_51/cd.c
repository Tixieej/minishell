/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 13:12:48 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/11 13:22:41 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*move_backwards(char *path, int *start)
{
	struct stat		buffer;
	int				len;
	char			*temp;

	temp = NULL;
	len = ft_strlen(path);
	while (path[len] != '/')
	{
		len--;
	}
	*start += 1;
	temp = ft_substr(path, 0, len);
	free(path);
	path = NULL;
	path = ft_strdup(temp);
	free(temp);
	if (stat(path, &buffer) == -1)
	{
		free(path);
		path = ft_strdup("/");
	}
	return (path);
}

static char	*move_forward(t_command *command, char *path, char *file)
{
	struct stat		buffer;
	char			*temp;

	temp = ft_strjoin(path, "/");
	free(path);
	path = ft_strjoin(temp, file);
	if (stat(path, &buffer) == -1)
	{
		command_not_found(command, file, "No such file or directory", 1);
		free(file);
		free(path);
		free(temp);
		return (NULL);
	}
	free(file);
	file = NULL;
	free(temp);
	return (path);
}

char	*backward_check(t_command *command, int len, int *start, char *path)
{
	if (command->args->content[*start + len] == '.'
		&& command->args->content[*start + len + 1] == '.')
	{
		if (command->args->content[*start + len + 2] == '.')
			*start += 2;
		else
			path = move_backwards(path, start);
	}
	return (path);
}

static char	*create_new_path(t_command *command,
									char *path, int start, int len)
{
	char	*file;

	file = NULL;
	while (command->args->content[start + len] != '\0')
	{
		start += len;
		len = 0;
		while (!ft_strchr("'.'/''\0'", command->args->content[start + len]))
			len++;
		if (len > 0)
		{
			file = ft_substr(command->args->content, start, len);
			path = move_forward(command, path, file);
			if (path == NULL)
				return (NULL);
		}
		path = backward_check(command, len, &start, path);
		len++;
	}
	return (path);
}

void	cd(t_command *command, char **env, int count, char *path)
{
	char	*old_path;

	old_path = NULL;
	if (cd_no_args(command, env, path) == -1)
		return ;
	path = getcwd(NULL, 0);
	if (path == NULL)
		error_handler("getcwd failure", NULL, command);
	old_path = ft_strdup(path);
	path = create_new_path(command, path, 0, 0);
	if (!path)
		return ;
	count = alter_env(&(*env), "PWD=", path);
	if (ft_strncmp(old_path, path, ft_strlen(old_path)) == 0
		&& ft_strncmp(old_path, path, ft_strlen(path)) == 0)
		command_not_found(command, command->args->content,
			"No such file or directory", 1);
	if (chdir(path) != 0)
		command_not_found(command, path, "No such file or directory", 1);
	free (path);
	free (old_path);
}
