/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/05 16:25:14 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include "ft_list.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef int	t_size_t;
void		prompt(void);
char		**ft_list_to_array(t_list *list);
char		*ft_append_path(char *str);
void		ft_execute(char **command, char **envp);
void		ft_list_push_back(t_list **begin_list, void *data);

/*
**LIBFT functions
*/
int			ft_strncmp(char *s1, char *s2, size_t n);
size_t		ft_strlen(char *str);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split(char const *s, char c);

#endif
