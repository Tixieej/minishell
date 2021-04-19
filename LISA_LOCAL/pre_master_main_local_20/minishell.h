/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/08 12:04:25 by livlamin      ########   odam.nl         */
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

typedef struct			s_command
{
	//struct s_command	*previous;
	char				*program;
	t_list				*args;
	int					pipe_left;
	int					pipe_right;
	int					fd_in;
	int					fd_out;
	t_list				*in_red;
	t_list				*out_red;
	struct s_command	*next;
}						t_command;


/*
** HULPFUNCTIE WEG!
*/
void			print_cur_struct(t_command *command);


int						main(int argc, char **argv, char **env);
void					error_handler(char *error, t_list **list, t_command *cmd);
t_command				*ft_create_linked_struct(char *data);
t_command				*ft_clear_linked_struct(t_command *command);
void					ft_struct_push_back(t_command **begin_list, char *data);
void					prompt(void);

/*
** tokenize functions?
*/
void					start_program(t_list *list, char **env);
t_list					*ft_create_elem(void *data);
void					ft_list_push_back(t_list **begin_list, void *data);

/*
** parse functions
*/
void					parser(t_list **list, char **env, t_command *command);
//t_command				*make_command(t_list **list);
//void            		non_buildin(t_list *list, char **env);
char					**list_to_array(t_list **list);
//void					ft_lstadd_front(t_list **lst, t_list *new);
void						redirection(t_command *command);

/*
** exec
*/
void					check_type(char **env, t_command *cmd);
pid_t					pipes(t_command *cmd);
void					external(t_command *cmd, char **env, int out_fd, pid_t process);
char					*ft_append_path(char *str);
void					ft_exec(char *path, t_command command, char **env, pid_t process);

/*
** env_path.c
*/
char					**make_path_array(char **envp);

/*
** env_pointers
*/
char					*check_env(char **env, char *var);
char					*get_pointer_env(char **env, char *var);

/*
** builtins
*/
void					cd(t_command *command, char **env, char *path);
void					echo(t_command *command);
void        			pwd(int fd);

/*
** signals
*/
void					handle_sigint(int sig);
void					handle_sigkill(int sig);
void					signal_handler(t_command *command);

#endif