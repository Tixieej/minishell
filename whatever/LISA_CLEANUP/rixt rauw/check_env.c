/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 14:10:50 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/09 16:49:37 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** if var is in env, return the value??
*/
char        *check_env(char **env, char *var)
{
    int 	count;
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
