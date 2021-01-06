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

# include <sys/wait.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "get_next_line.h"

# include <stdio.h> // WEGHALEN PRINTF
# define PRINT(a,b) printf(a" %s:%i (%s)\n", b, __FILE__, __LINE__, __FUNCTION__);
// PRINT("kijk: %p", temp)
// printf("temp: %s:%i %s\n", __FILE__, __LINE__, __FUNCTION__);	

// typedef	struct		s_list
// {
// 	struct s_list	*next;
// 	void			*data;
// }					t_list;


int                 main(int argc, char **argv);

#endif
