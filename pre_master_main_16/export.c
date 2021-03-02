/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 14:03:48 by rde-vrie      #+#    #+#                 */
/*   Updated: 2021/03/02 17:05:45 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_var(char *new_arg, char **env)
{
	int exist = -1;
	int i = 0;

	while (env[i])
	{

		char *var_old = ft_split(env[i], '=')[0];
		char *var_new = ft_split(new_arg, '=')[0];
		size_t max_len = ft_strlen(var_old);
		if (ft_strlen(var_new) > max_len)
			max_len = ft_strlen(var_new);
		if (ft_strncmp(env[i], new_arg, max_len) == 0)
		{
			printf("\tstaat erin\n");
			exist = i;
			break ;
		}
		i++;
	}
	if (exist == -1)
		printf("\tzet new arg erin\n");
		count = array_length(env) + 1;
	else
	{
		printf("\t%s staat op plek %i\n", new_arg, i);
		if (ft_strchr(new_arg, '='))
		{
			printf("\t= teken in [%s], overschrijf var\n", new_arg);
		}
	}
}

static void	print_envs(char **env)
{
	//char *var;
	//char *value;
	int i = 0;

	while (env[i])
	{
		char *var = ft_split(env[i], '=')[0];
		char *is_sign = ft_strchr(env[i], '=');
		char *value = ft_substr(is_sign, 1, ft_strlen(is_sign) - 1);
		printf("declare -x ");
		printf("%s=", var);
		printf("\"%s\"\n", value);
		i++;
	}
}

void	export_func(t_command *command, char **env)
{
	int	i;
	t_list *begin_arg;

	i = 0;
	if (command->args == NULL)
	{
		print_envs(env);
		return ;
	}
	begin_arg = command->args;
	while (command->args)
	{
		if (ft_isalpha(*(command->args->content)) == 1 || *(command->args->content) == '_')
		{
			printf("\t[%s] komt erin\n", command->args->content);
			add_var(command->args->content, env);
		}
		else
			printf("minishell: export: `%s': not a valid identifier\n", command->args->content);
		command->args = command->args->next;
	}
}

//bash: syntax error near unexpected token `)'
// na export -bla=5: (maar dit is undef behaviour, want wij hoeven niet met opties)
//bash: export: -b: invalid option
//export: usage: export [-nf] [name[=value] ...] or export -p
