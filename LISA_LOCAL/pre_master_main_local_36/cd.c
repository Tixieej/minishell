/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 13:12:48 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/08 11:55:22 by livlamin      ########   odam.nl         */
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

static int	alter_env(char **env, char *var, char *path)
{
	int		count;
	int		len_var;
	char	*temp;

	temp = NULL;
	len_var = ft_strlen(var);
	count = 0;
	while (env[count])
	{
		if (!ft_strncmp(env[count], var, len_var))
		{
			free(env[count]);
			env[count] = NULL;
			temp = ft_strdup("PWD=");
			env[count] = ft_strjoin(temp, path);
			free(temp);
			return (count);
		}
		count++;
	}
	return (0);
}

static char	*move_forward(char *path, char *file)
{
	struct stat		buffer;
	char			*temp;

	temp = ft_strjoin(path, "/");
	free(path);
	path = ft_strjoin(temp, file);
	if (stat(path, &buffer) == -1)
	{
		printf("minishell: %s: Not a directory\n", file);
		free(file);
		free(path);
		free(temp);
		return (NULL);
	}
	free(temp);
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
			path = move_forward(path, file);
			if (path == NULL)
				return (NULL);
			free(file);
			file = NULL;
		}
		if (command->args->content[start + len] == '.'
			&& command->args->content[start + len + 1] == '.')
		{
			if (command->args->content[start + len + 2] == '.')
				start += 2;
			else
				path = move_backwards(path, &start);
		}
		len++;
	}
	return (path);
}

void	cd(t_command *command, char **env, int count)
{
	char	*path;
	char	*old_path;

	path = NULL;
	old_path = NULL;
	if (command->args == NULL)
	{
		path = check_env(env, "HOME=");
		if (path == NULL)
			printf("minishell: HOME= non-existing\n");
		if (chdir(path) != 0)
			printf("minishell: %s: path non-existing\n", path);
		free(path);
		return ;
	}
	path = getcwd(NULL, 0);
	if (path == NULL)
		error_handler("getcwd failure", NULL, command);
	old_path = ft_strdup(path);
	path = create_new_path(command, path, 0, 0);
	if (!path)
		return ;
	count = alter_env(&(*env), "PWD=", path);
	if (ft_strncmp(old_path, path, ft_strlen(old_path)) == 0)
		printf("minshell: %s: No such file or directory\n", command->args->content);
	if (chdir(path) != 0)
		printf("minshell: %s: No such file or directory\n", path);
	free (path);
	free (old_path);
}
