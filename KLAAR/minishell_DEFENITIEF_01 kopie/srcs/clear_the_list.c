/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_the_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/20 17:09:24 by rixt          #+#    #+#                 */
/*   Updated: 2021/04/20 17:09:45 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_the_list(t_base *base)
{
	if (base->list)
	{
		ft_lstclear(&base->list, free);
		base->list = NULL;
	}
}
