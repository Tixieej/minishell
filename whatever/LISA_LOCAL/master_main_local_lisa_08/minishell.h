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

// typedef struct		s_command
// {
// 	char			*program;
// 	char			**args;//dit is al een array
// 	//redirection
// 	//etc ..
// }					t_command;


    typedef struct s_command 
	{
		// struct	s_command *previous;
        struct	s_command *next;
		char	*program;
        char	**args;
        int		pipe_left;
        int		pip_right;
		int		redirection;
    } 				t_command;

// 	typedef struct		s_list
// {
// 	struct s_list	*next;
// 	void			*content;
// }					t_list;

	// typedef struct		s_struct
	// {
    //     struct s_command command;
    //     struct s_struct_list *next;
	// }					t_struct;


    // typedef struct Schedule {
    //     char name[10];
    //     char description[10];
    //     int hours;
    //     int workordernum;
    // } Work;

    // typedef struct linkedlist {
    //     struct Schedule work;
    //     struct linkedlist *next;
    // } Node;

int					main(int argc, char **argv, char **env);

/*tokenize functions?*/
void            	start_program(t_list *list, char **env);
t_list				*ft_create_elem(void *data);
void				ft_list_push_back(t_list **begin_list, void *data);
void                check_type(t_list **list, char **env);

/*parse functions*/
void            	non_buildin(t_list *list, char **env);
char				**ft_list_to_array(t_list *list);
char				*ft_append_path(char *str);
void				ft_exec(char *path, t_command command, char **envp);

/*env_path.c*/
char				**make_path_array(char **envp);

#endif
