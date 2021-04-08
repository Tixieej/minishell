/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 14:03:48 by rde-vrie      #+#    #+#                 */
/*   Updated: 2021/04/02 13:43:50 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_to_array(char **old_array, char *new_arg)
{
	char	**new_array;
	int		count;
	int		i;

	count = array_length(old_array) + 2;
	new_array = (char **)malloc(sizeof(char *) * count);
	if (!new_array)
		return (NULL);
	i = 0;
	while (old_array[i])
	{
		new_array[i] = ft_strdup(old_array[i]);
		free(old_array[i]);
		i++;
	}
	new_array[i] = ft_strdup(new_arg);
	new_array[i + 1] = NULL;
	free(old_array);
	return (new_array);
}

static void	add_var(char *new_arg, char ***env)
{
	int		exist;
	int		i;

	exist = -1;
	i = 0;
	while ((*env)[i] && exist == -1)
	{
		exist = locate_var((*env)[i], new_arg);
		i++;
	}
	i--;
	if (exist == -1)
		*env = add_to_array(*env, new_arg);
	else
	{
		if (ft_strchr(new_arg, '='))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(new_arg);
		}
	}
}

static void	write_one_env(char *var, char *value, char *is_sign)
{
	write(1, "declare -x ", 11);
	write(1, var, ft_strlen(var));
	if (is_sign)
	{
		write(1, "=\"", 2);
		write(1, value, ft_strlen(value));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

static void	print_envs(char **env)
{
	char	*var;
	char	**cur_env;
	char	*value;
	char	*is_sign;
	int		i;

	i = 0;
	while (env[i])
	{
		cur_env = ft_split(env[i], '=');
		var = cur_env[0];
		is_sign = ft_strchr(env[i], '=');
		value = ft_substr(is_sign, 1, ft_strlen(is_sign) - 1);
		write_one_env(var, value, is_sign);
		i++;
		free_array(cur_env);
		free(value);
	}
}

void	export_func(t_command *command, char ***env)
{
	int		i;
	t_list	*begin_arg;

	i = 0;
	if (command->args == NULL)
	{
		print_envs(*env);
		return ;
	}
	begin_arg = command->args;
	while (command->args)
	{
		if (ft_isalpha(*(command->args->content)) == 1 || \
			*(command->args->content) == '_')
			add_var(command->args->content, env);
		else
		{
			write(2, "minishell: export: `", 20);
			write(2, command->args->content, ft_strlen(command->args->content));
			write(2, "': not a valid identifier\n", 26);
			command->not_found = 1;
		}
		command->args = command->args->next;
	}
	command->args = begin_arg;
}
