/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/24 11:42:42 by rixt          #+#    #+#                 */
/*   Updated: 2021/04/24 11:44:51 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_str(char *str, char *str_temp, char *str_end)
{
	free(str);
	str = ft_strjoin(str_temp, str_end);
	return (str);
}

void	set_exp_values(t_exp *exp_values)
{
	exp_values->start = 1;
	exp_values->len = 0;
}
