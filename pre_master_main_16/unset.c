/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 14:05:53 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/09 10:36:10 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_length(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	unset(t_command *command, char ***env)
{
	char	*var_name;
	char	*env_var;
	int		len_var;
	int		count;
	char	**new_env;
	int		j = 0;

	if (!(command->args))
		return ;
	var_name = command->args->content;
	env_var = check_env(*env, var_name);
	if (!env_var)
	{
		printf("\tkomt niet voor in env\n");
		return ;
	}
	count = array_length(*env);
	printf("\t COUNT = %i\n", count);
	new_env = malloc(sizeof(char *) * (count));
	if (!new_env)//free hier ook dingen?
		printf("ERROR\n");
	printf("\tnew_env = %p\n", new_env);
	new_env[count] = NULL;
	int i = 0;
	len_var = ft_strlen(var_name);
	//while(1);//hierboven zitten geen leaks meer
	while ((*env)[i+j])
	{
		printf("env %i\t(*env)[i+j] = \t%p = %s\n", i+j, (*env)[i+j], (*env)[i+j]);
		if (ft_strncmp(var_name, (*env)[i + j], len_var) != 0)
		{
			new_env[i] = ft_strdup((*env)[i + j]);
		//	printf("\tnew_env = %p, new_env[i] = %p\n", new_env, new_env[i]);
		//	printf("\t(*env)[i+j] = \t%p\n", (*env)[i+j]);
			i++;
		}
		else
			j++;
	}
	//while(1);//2 leaks in while loop hierboven
	free_array(*env);
	*env = new_env;//waar gaat de vorige *env heen?
	printf("\tnew_env = \t%p\n", new_env);// het is iets wat vlak hiervoor is gemalloct?
	printf("\tunset env = \t%p\n", *env);
	printf("\tenv = \t\t%p\n", env);

/*
	i = 0;
	//dit zijn checks, mogen weg als het klopt.
	while (new_env[i])
	{
		
		printf("\t\tnew_env %i = %s\n", i, new_env[i]);
		i++;
	}*/
}
