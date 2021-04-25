/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 13:12:48 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/01 10:04:02 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*move_backwards(char *path, int *start)
{
	int len;

	len = ft_strlen(path);
	while (path[len] != '/')
	{
		len--;
	}
	*start += 2;
	return (ft_substr(path, 0, len));
}

static void		*alter_env(char **env, char *var, char *file)
{
	int count;
	int	len_var;

	len_var = ft_strlen(var);
	count = 0;
	while (env[count])
	{
		if (!ft_strncmp(env[count], var, len_var))
		{
			env[count] = ft_strjoin(env[count], "/");
			env[count] = ft_strjoin(env[count], file);
		}
		count++;
	}
	return (NULL);
}

static int		move_forward(char **env, char **path, char *file)
{
	struct stat		buffer;

	alter_env(&(*env), "PWD=", file);
	*path = ft_strjoin(*path, "/");
	*path = ft_strjoin(*path, file);
	if (stat(*path, &buffer) == -1)
	{
		printf("minishell: %s: Not a directory\n", file);
		free(file);
		return (-1);
	}
	free(file);
	file = NULL;
	return (0);
}

static char		*create_new_path(t_command *command, char **env,
									char *path, int start)
{
	char	*file;
	int		len;

	file = NULL;
	len = 0;
	while (command->args->content[start + len] != '\0')
	{
		start += len;
		len = 0;
		while (!ft_strchr("'.'/''\0'", command->args->content[start + len]))
			len++;
		if (len > 0)
		{
			file = ft_substr(command->args->content, start, len);
			if (move_forward(env, &path, file) == -1)
				return (NULL);
		}
		if (command->args->content[start + len] == '.' &&
				command->args->content[start + len + 1] == '.')
			path = move_backwards(path, &start);
		len++;
	}
	return (path);
}

void			cd(t_command *command, char **env)
{
	char *path;

	path = NULL;
	path = getcwd(NULL, 0);
	if (path == NULL)
		error_handler("getcwd failure", NULL, command);
	if (command->args == NULL)
	{
		path = check_env(env, "HOME=");
		if (path == NULL)
			printf("minishell: HOME= non-existing\n");
		if (chdir(path) != 0)
			printf("minishell: %s: path non-existing\n", path);
		return ;
	}
	path = create_new_path(command, env, path, 0);
	if (!path)
		return ;
	if (chdir(path) != 0)
	{
		printf("minishell: %s: Not a directory\n", path);
		return ;
	}
	free(path);
}
