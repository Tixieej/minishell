/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 14:05:53 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/09 17:11:13 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

static char	**make_new_env(char **new_env, char *var_name, char ***env)
{
	int	len_var;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len_var = ft_strlen(var_name);
	while ((*env)[i + j])
	{
		if (ft_strncmp(var_name, (*env)[i + j], len_var) != 0)
		{
			new_env[i] = ft_strdup((*env)[i + j]);
			i++;
		}
		else
			j++;
	}
	return (new_env);
}

void	unset(t_command *command, char ***env)
{
	char	*var_name;
	char	*env_var;
	int		count;
	char	**new_env;

	if (!(command->args))
		return ;
	var_name = command->args->content;
	env_var = check_env(*env, var_name);
	if (!env_var)
	{
		printf("\tkomt niet voor in env\n");
		return ;
	}
	free(env_var);
	count = array_length(*env);
	new_env = malloc(sizeof(char *) * (count));
	if (!new_env)
		printf("ERROR\n");
	new_env[count - 1] = NULL;
	new_env = make_new_env(new_env, var_name, env);
	free_array(*env);
	*env = new_env;
}
