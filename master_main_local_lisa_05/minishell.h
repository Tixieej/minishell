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
# include <unistd.h> //mogen we die gebruiken? voor write
# include <sys/stat.h> //stat
# include <stdio.h> // WEGHALEN PRINTF

typedef struct		s_command
{
	char			*program;
	char			**args;//dit is al een array
	//redirection
	//etc ..
}					t_command;

int					main(int argc, char **argv, char **env);
void				error(char *str, int ret);

/*tokenize functions?*/
void            	start_program(t_list *list, char **env);
t_list				*ft_create_elem(void *data);
void				ft_list_push_back(t_list **begin_list, void *data);
void                check_type(t_list **list, char **env);

/*parse functions*/
// void            	ft_parse(t_list *list, char **env);
void				ft_parse(t_list *list, char **envp, t_list *begin);
char				**ft_list_to_array(t_list *list);
char				*ft_append_path(char *str);
void				ft_exec(char *path, t_command command, char **envp);

/*env_path.c*/
char				**make_path_array(char **envp);

#endif
