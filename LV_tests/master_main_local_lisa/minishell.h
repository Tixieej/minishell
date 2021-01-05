/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/10/23 16:03:08 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/wait.h>
#include <stdlib.h>

typedef	struct		s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

t_list              *ft_create_elem(void *data);
void				ft_list_push_back(t_list **begin_list, void *data);
int                 main(int argc, char **argv);

#endif
