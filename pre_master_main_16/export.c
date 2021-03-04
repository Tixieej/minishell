/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 14:03:48 by rde-vrie      #+#    #+#                 */
/*   Updated: 2021/03/04 17:30:31 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//MALLOC PROTECTIONS

static char	**add_to_array(char **old_array, char *new_arg)
{
	char	**new_array;
	int		count = array_length(old_array) + 2;
	int		i;

	new_array = (char **)malloc(sizeof(char *) * count);
	if (!new_array)
		return (NULL);
	i = 0;
	while (old_array[i])
	{
		new_array[i] = ft_strdup(old_array[i]);
		i++;
	}
	new_array[i] = ft_strdup(new_arg);
	new_array[i + 1] = NULL;
	//free(old_array);
	return (new_array);
}

static void	add_var(char *new_arg, char ***env)
{
	int		exist = -1;
	int		i = 0;
	char	*var_old;
	char	*var_new;
	size_t	max_len;

	while ((*env)[i])
	{
		var_old = ft_split((*env)[i], '=')[0];
		var_new = ft_split(new_arg, '=')[0];
		max_len = ft_strlen(var_old);
		if (ft_strlen(var_new) > max_len)
			max_len = ft_strlen(var_new);
		if (ft_strncmp((*env)[i], new_arg, max_len) == 0)
		{
			exist = i;
			break ;
		}
		i++;
	}
	if (exist == -1)
		*env = add_to_array(*env, new_arg);
	else
	{
		if (ft_strchr(new_arg, '='))
		{
			//free(env[i]);
			(*env)[i] = ft_strdup(new_arg);
		}
	}
}

static void	print_envs(char **env)
{
	char	*var;
	char	*value;
	char	*is_sign;
	int		i;

	i = 0;
	while (env[i])
	{
		var = ft_split(env[i], '=')[0];
		is_sign = ft_strchr(env[i], '=');
		value = ft_substr(is_sign, 1, ft_strlen(is_sign) - 1);
		printf("declare -x ");
		printf("%s=", var);
		printf("\"%s\"\n", value);
		i++;
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
		if (ft_isalpha(*(command->args->content)) == 1 || *(command->args->content) == '_')
			add_var(command->args->content, env);
		else
			printf("minishell: export: `%s': not a valid identifier\n", command->args->content);
		command->args = command->args->next;
	//	begin_arg = command->args;
	}
}
