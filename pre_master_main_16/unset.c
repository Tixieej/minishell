/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 14:05:53 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/08 17:35:59 by rde-vrie      ########   odam.nl         */
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
	printf("\targ = [%s], var = [%s]\n", command->args->content, var_name);
	env_var = check_env(*env, var_name);//get the right env variable
	printf("\tenv_var = [%s]\n", env_var);
	// check of var in env lijst staat, zonee, ga uit de functie.
	if (!env_var)
	{
		printf("\tkomt niet voor in env\n");
		return ;
	}
	count = array_length(*env);
	new_env = malloc(sizeof(char *) * (count));//null aan einde
	if (!new_env)//free hier ook dingen?
		printf("ERROR\n");
	new_env[count] = NULL;
	int i = 0;
	len_var = ft_strlen(var_name);
	//while(1);//hierboven zitten geen leaks meer
	while ((*env)[i+j])
	{
		//printf("env %i = %s\n", i+j, (*env)[i + j]);
		//2 while loops maken en tussendoor een keer env plussen
		if (ft_strncmp(var_name, (*env)[i + j], len_var) != 0)//als het niet gelijk is
		{
			new_env[i] = ft_strdup((*env)[i + j]);
			i++;
		}
		else
			j++;
	}
	*env = new_env;
	// printf("\tnew_env = \t%p\n", new_env);
	// printf("\tunset env = \t%p (wil je hetzelfde)\n", *env);
	// printf("\tenv = \t%p (hoort anders)\n", env);
	i = 0;
	//dit zijn checks, mogen weg als het klopt.
	while (new_env[i])
	{
		
		//printf("\t\tnew_env %i = %s\n", i, new_env[i]);
		i++;
	}
	i = 0;
	while ((*env)[i])
	{
		//printf("\t\tenv %i = %s\n", i, (*env)[i]);
		i++;
	}
}
