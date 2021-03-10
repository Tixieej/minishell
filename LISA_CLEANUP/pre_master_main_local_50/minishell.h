/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/10 12:33:21 by livlamin      ########   odam.nl         */
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
# include <signal.h>

typedef struct s_command
{
	char				*program;
	t_list				*args;
	int					pipe_left;
	int					pipe_right;
	int					fd_in;
	int					fd_out;
	int					pipe_check;
	t_list				*in_red;
	t_list				*out_red;
	struct s_command	*next;
}						t_command;

/*
** HULPFUNCTIE WEG!
*/
void			print_cur_struct(t_command *command);

int				main(int argc, char **argv, char **env);
void			error_handler(char *error, t_list *list, t_command *cmd);
t_command		*ft_create_linked_struct(char *data);
t_command		*ft_clear_linked_struct(t_command *command);
t_command		*ft_clear_linked_struct_deep_shadow(t_command *command); //WEG?
void			ft_struct_push_back(t_command **begin_list, char *data);
void			prompt(void);

/*
** tokenize functions?
*/
void			divide_input(t_list **list, char *line, size_t len,
					unsigned int start);
t_list			*ft_create_elem(void *data);
void			ft_list_push_back(t_list **begin_list, void *data);

/*
** parse functions
*/
void			parser(t_list **list, char **env, t_command *command);
//t_command				*make_command(t_list **list); //
//void            		non_builtin(t_list *list, char **env);
char			**list_to_array(t_list **list);
//void					ft_lstadd_front(t_list **lst, t_list *new);
int				redirection(t_command *command);

/*
** exec
*/
void			check_type(char **env, t_command *cmd);
void			check_type_two(char **env, t_command *command, pid_t process);
int				in_redirect(t_command *cmd);
int				out_redirect(t_command *cmd);
pid_t			pipes(char **env, t_command *cmd, pid_t process, int count);
void			external(t_command *cmd, char **env, pid_t process);
char			*ft_append_path(char *str);
void			t_exec(char *path, t_command command, char **env,
					pid_t process);

/*
** env_path.c
*/
char			**make_path_array(char **envp);

/*
** env_pointers
*/
char			*check_env(char **env, char *var);
char			*get_pointer_env(char **env, char *var);
int				alter_env(char **env, char *var, char *path);

/*
** builtins
*/
void			cd(t_command *command, char **env, int count, char *path);
void			echo(t_command *command, char *s);
void			pwd(t_command *command);
void			exit_func(t_command *command);
void			env_check(t_command *command, char **env, int len);
int				cd_no_args(t_command *command, char **env, char *path);

/*
** signals
*/
void			signal_handler(int sig);

#endif
