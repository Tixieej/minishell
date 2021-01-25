/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/16 13:55:44 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <stdlib.h>
//# include "libft/libft.h"
//# include "get_next_line.h"
# include <unistd.h> //mogen we die gebruiken? voor write
# include <sys/stat.h> //stat
# include <stdio.h> // WEGHALEN PRINTF

typedef struct		s_command
{
	char			*program;
	char			**args;//dit is al een array
	int				pipe_left;
	int				pipe_right;
	//redirection
	//etc ..
}					t_command;

typedef struct		s_list
{
	struct s_list	*next;
	void			*content;
}					t_list;


int					main(void);
t_list				*ft_create_elem(void *data);
void				ft_list_push_back(t_list **begin_list, void *data);

/*tokenize functions?
void				start_program(t_list *list, char **env);
t_list				*ft_create_elem(void *data);
void				ft_list_push_back(t_list **begin_list, void *data);

parse functions
t_command			parser(t_list **list);
char				**ft_list_to_array(t_list **list);
char				*ft_append_path(char *str);

exec 
void				check_type(t_list **list, char **env);
void				external(t_command cmd, char **env);
void				ft_exec(char *path, t_command command, char **env);

env_path.c
char				**make_path_array(char **env);
*/
#endif
