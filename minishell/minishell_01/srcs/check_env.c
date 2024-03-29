/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 14:10:50 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/18 11:39:16 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_env(char **env, char *var)
{
	int		count;
	size_t	max_len;
	char	**cur_env;

	max_len = ft_strlen(var);
	count = 0;
	while (env[count])
	{
		cur_env = ft_split(env[count], '=');
		if (ft_strlen(env[count]) > max_len)
			max_len = ft_strlen(cur_env[0]);
		if (!ft_strncmp(env[count], var, max_len))
		{
			free_array(cur_env);
			return (ft_strdup(&env[count][max_len]));
		}
		count++;
		free_array(cur_env);
	}
	return (NULL);
}

char	*get_pointer_env(char **env, char *var)
{
	int		count;
	int		len_var;

	len_var = ft_strlen(var);
	count = 0;
	while (env[count])
	{
		if (!ft_strncmp(env[count], var, len_var))
			return (env[count]);
		count++;
	}
	return (NULL);
}

int	alter_env(char **env, char *var, char *path)
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

int	cd_no_args(t_command *command, char **env, char *path)
{
	if (command->args == NULL)
	{
		path = check_env(env, "HOME=");
		if (path == NULL)
			printf("minishell: HOME= non-existing\n");
		if (chdir(path) != 0)
			printf("minishell: %s: path non-existing\n", path);
		free(path);
		return (-1);
	}
	return (0);
}

void	set_oldpath(char **env, char *old_path)
{
	int		count;
	int		len_var;
	char	*temp;

	temp = ft_strdup("OLDPWD=");
	len_var = ft_strlen(old_path);
	count = 0;
	while (env[count])
	{
		if (!ft_strncmp(env[count], "OLDPWD=", 7))
		{
			free(env[count]);
			env[count] = ft_strjoin(temp, old_path);
			free(temp);
			break ;
		}
		count++;
	}
}
