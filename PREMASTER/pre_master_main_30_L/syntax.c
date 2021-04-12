/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 14:21:36 by rde-vrie      #+#    #+#                 */
/*   Updated: 2021/04/12 16:42:36 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

syntax_error(t_list *list)
{
	t_list *cur_list;

	cur_list = list;
	if (ft_strchr("", cur_list))//als cur list = ;<>| en dan ;<>|
	{
		if (cur_list->next)
		{
			write(2, "minishell: syntax error near unexpected token `", ft_strlen());
			write(2, cur_list, ft_strlen());
			write(2, "'\n", 2);
		}
	}


}
