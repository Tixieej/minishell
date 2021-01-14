/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 16:29:08 by rixt          #+#    #+#                 */
/*   Updated: 2021/01/12 10:26:26 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char		**make_path_array(char **envp)
{
	char	**pre_paths;
	char	**paths;
	char	**tmp = envp;
	
	while (*tmp)
	{
		if (ft_strncmp("PATH=", *tmp, 5) == 0)
		{
			pre_paths = ft_split(*tmp, '=');//later misschien de hele env splitten op var en values, dan daaruit de PATH lezen?
			paths = ft_split(pre_paths[1], ':');
		}
		tmp++;
	}
	return (paths);
}
