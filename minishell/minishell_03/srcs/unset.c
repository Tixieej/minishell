/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 14:05:53 by rixt          #+#    #+#                 */
/*   Updated: 2021/04/22 16:41:41 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_env_export(char **env, char *var)
{
	int		count;
	size_t	max_len;
	char	**cur_env;

	max_len = ft_strlen(var);
	count = 0;
	while (env[count])
	{
		cur_env = ft_split(env[count], '=');
		if (max_len != ft_strlen(cur_env[0]))
		{
			free_array(cur_env);
			count++;
			continue ;
		}
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

void	unset_var(t_command *command, char ***env)
{
	char	*var_name;
	char	*env_var;
	int		count;
	char	**new_env;

	var_name = command->args->content;
	env_var = check_env_export(*env, var_name);
	if (!env_var)
		return ;
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

static int	valid_check(char *s)
{
	int	i;

	if (ft_isalpha(*(s)) != 1 && !(*s == '_'))
		return (-1);
	i = 1;
	while (s[i])
	{
		if (ft_isalnum(s[i]) != 1 && (*s != '_'))
			return (-1);
		i++;
	}
	return (1);
}

void	unset(t_command *command, char ***env)
{
	char	*tmp;
	char	*message;
	t_list	*begin_arg;

	tmp = NULL;
	message = NULL;
	if (!(command->args))
		return ;
	begin_arg = command->args;
	while (command->args)
	{
		if (valid_check(command->args->content) == 1)
			unset_var(command, env);
		else
		{
			tmp = ft_strjoin("unset: `", command->args->content);
			message = ft_strjoin(tmp, "'");
			command_not_found(command, message, "not a valid identifier", 1);
			free(message);
			free(tmp);
		}
		command->args = command->args->next;
	}
	command->args = begin_arg;
}
