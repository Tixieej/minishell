/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 13:12:48 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/26 14:16:49 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*move_backwards(char *path)
{
	int len;

	len = ft_strlen(path);
	while (path[len] != '/')
	{
		len--;
	}
	return(ft_substr(path, 0, len));
}

void        *alter_env(char **env, char *var, char *file)
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

static int		move_forward(char **env, char *path, char *file)
{
	struct stat		buffer;
	// char	*file;

	// file = NULL;
	// file = ft_substr(command->args->content, start, len);
	alter_env(&(*env), "PWD=", file);
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, file);
	if (stat(path, &buffer) == -1)
	{
		printf("minishell: %s: Not a directory\n", file);
		free(file);
		return (-1);
	}
	free(file);
	file = NULL;
	return (0);
}

void        cd(t_command *command, char **env, char *path, int start)
{
	int				len;
	char			*file;

	len = 0;
	file = NULL;
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
		return;
	}
	while (command->args->content[start + len] != '\0')
	{
		start += len;
		len = 0;
		// while (command->args->content[start + len] != '.' && command->args->content[start + len] != '/' && command->args->content[start + len] != '\0')
		// 	len++;
		while (!ft_strchr("'.'/''\0'", command->args->content[start + len]))
			len++;
		if (len > 0)
		{
			file = ft_substr(command->args->content, start, len);
			if (move_forward(env, path, file) == -1)
				return;
		}
			
		if (command->args->content[start + len] == '.' && command->args->content[start + len + 1] == '.')
		{
			path = move_backwards(path);
			start += 2;
		}
		len++;
	}
	if (chdir(path) != 0)
	{
		printf("minishell: %s: Not a directory\n", path);
		return;
	}
	free(path);
}