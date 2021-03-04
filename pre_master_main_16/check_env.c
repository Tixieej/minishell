/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 14:10:50 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/04 16:12:13 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** if var is in env, return the value??
*/
char        *check_env(char **env, char *var)
{
    int count;
	int	len_var;

	len_var = ft_strlen(var);
    count = 0;
    while (env[count])
    {
        if (!ft_strncmp(env[count], var, len_var))
			return(ft_strdup(&env[count][len_var]));     
        count++;
    }
    return (NULL);
}

char        *get_pointer_env(char **env, char *var)
{
    int count;
	int	len_var;

	len_var = ft_strlen(var);
    count = 0;
    while (env[count])
    {
        if (!ft_strncmp(env[count], var, len_var))
			return(env[count]);   
        count++;
    }
    return (NULL);
}
