/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 13:12:48 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/04 11:49:29 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*move_backwards(char *path, int *start)
{
	struct stat		buffer;
	int				len;
	char			*temp;

	len = ft_strlen(path);
	temp = NULL;
	while (path[len] != '/')
	{
		len--;
	}
	*start += 2;
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

static void		alter_env(char **env, char *var, char *file)
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
			temp = ft_strjoin(env[count], "/");
			printf("temp: %p\n", temp);
			free(env[count]);
			env[count] = NULL;
			env[count] = ft_strjoin(temp, file);
			
			// printf("path: %p\n", path);
			// temp = ft_strjoin("/", file);
			// printf("temp1: %p\n", temp);
			// env[count] = ft_strjoin(env[count], temp);
			// printf("env: %p\n", env[count]);
			free(temp);
			temp = NULL;
		}
		count++;
	}
}

static char		*move_forward(char **env, char *path, char *file)
{
	struct stat		buffer;
	char			*temp;

	alter_env(&(*env), "PWD=", file);
	temp = ft_strjoin(path, "/");
	printf("temp: %p\n", temp);
	free(path);
	path = ft_strjoin(temp, file);
	printf("path: %p\n", path);
	if (stat(path, &buffer) == -1)
	{
		printf("minishell: %s: Not a directory\n", file);
		free(file);
		free(path);
		return (NULL);
	}
	free(temp);
	return (path);
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
			if ((path = move_forward(env, path, file)) == NULL)
				return (NULL);
			free(file);
			file = NULL;
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