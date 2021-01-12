/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_list.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:34:22 by livlamin      #+#    #+#                 */
/*   Updated: 2019/08/21 17:58:07 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_LIST_H
# define FT_LIST_H

typedef	struct		s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

t_list              *ft_create_elem(void *data);
void				ft_list_push_back(t_list **begin_list, void *data);

#endif
