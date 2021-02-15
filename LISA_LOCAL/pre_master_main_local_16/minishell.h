/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/04 14:42:38 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct			s_command
{
	//struct s_command	*previous;
	char				*program;
	t_list				*args;
	int					pipe_left;
	int					pipe_right;
	t_list				*in_red;
	t_list				*out_red;
	struct s_command	*next;
}						t_command;

int						main(int argc, char **argv, char **env);
void					error_handler(char *error, t_list **list, t_command *cmd);
t_command				*ft_create_linked_struct(char *data);
void					ft_struct_push_back(t_command **begin_list, char *data);
int						redirection(t_command *command);
char					*check_env(char **env, char *var);

/*
** tokenize functions?
*/
void					start_program(t_list *list, char **env);
t_list					*ft_create_elem(void *data);
void					ft_list_push_back(t_list **begin_list, void *data);
void					parser(t_list **list, char **env, t_command *command);
pid_t					pipes(t_command *cmd);

/*
** parse functions
*/
//t_command				*make_command(t_list **list);
//void            		non_buildin(t_list *list, char **env);
char					**list_to_array(t_list **list);
char					*ft_append_path(char *str);
//void					ft_lstadd_front(t_list **lst, t_list *new);

/*
** exec
*/
void					check_type(char **env, t_command *cmd);
void					external(t_command *cmd, char **env, int fd, pid_t process);
void					ft_exec(char *path, t_command command, char **env, pid_t process);

/*
** env_path.c
*/
char					**make_path_array(char **envp);

/*
** builtins
*/
void					cd(t_command *command, char **env);
void					echo(t_command *command, int fd);
void        			pwd(int fd);
#endif