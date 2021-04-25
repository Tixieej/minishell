/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 17:42:32 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/11 17:44:46 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	locate_var(char *cur_env, char *new_arg)
{
	size_t	max_len;
	char	**env_old;
	char	**env_new;
	char	*var_old;
	char	*var_new;

	env_old = ft_split(cur_env, '=');
	var_old = env_old[0];
	env_new = ft_split(new_arg, '=');
	var_new = env_new[0];
	max_len = ft_strlen(var_old);
	if (ft_strlen(var_new) > max_len)
		max_len = ft_strlen(var_new);
	if (ft_strncmp(cur_env, new_arg, max_len) == 0)
	{
		free_array(env_old);
		free_array(env_new);
		return (1);
	}
	free_array(env_old);
	free_array(env_new);
	return (-1);
}
