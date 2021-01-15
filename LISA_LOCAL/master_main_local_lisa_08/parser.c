/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/12/01 15:55:26 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

    // typedef struct s_command 
	// {
    //     char	*program;
    //     char	**args;
    //     int		pipe_left;
    //     int		pip_right;
	// 	int		redirection;
    // } 				t_command;

	// typedef struct		s_struct_list
	// {
    //     struct s_command command;
    //     struct s_struct_list *next;
	// }					t_struct_list;

static t_struct		*ft_create_struct(t_command command)
{
	t_struct 	*list_struct;

	list_struct = malloc(sizeof(t_struct));
	if (list_struct)
	{
		list_struct->command = command;
		list_struct->next = NULL;
	}
	return (list_struct);
}
// t_list		*ft_create_elem(void *data)
// {
// 	t_list *list;

// 	list = malloc(sizeof(t_list));
// 	if (list)
// 	{
// 		list->content = data;
// 		list->next = NULL;
// 	}
// 	return (list);
// }


static void		ft_struct_list_push_back(t_struct **begin_struct, t_command command)
{
	t_struct	*temp;

	temp = *begin_struct;
	if (*begin_struct)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = ft_create_struct(command);
	}
	else
		*begin_struct = ft_create_struct(command);
}

static void	parser(t_list **list, char **env)
{
	t_struct 	*list_struct;
	t_command	command;
	t_list		*begin;

	begin = *list;
	list_struct = NULL;
	while (begin)
	{
		if (ft_strncmp((const char *)begin->content, "cat", 3) == 0)
			ft_struct_list_push_back(&list_struct, command);
		begin = begin->next;
	}
	
}

void    check_type(t_list **list, char **env)
{
	parser(list, env);
	// t_list	*begin;

	// begin = *list;
	// while (begin)
	// {
	// 	if (ft_strncmp((const char *)begin->content, "cat", 3) == 0)
	// 		printf("cat type\n");
	// 	if (ft_strncmp((const char *)begin->content, "cp", 2) == 0)
	// 		non_buildin(*list, env);
	// 	if (ft_strncmp((const char *)begin->content, "echo", 4) == 0)
	// 		printf("echo type\n");
	// 	begin = begin->next;
	// }
	// begin = *list;
}










// void	error(char *str, int ret)
// {
// 	printf("%s\n", str);
// 	if (ret < 0)
// 		exit(-1);
// }

// void    check_type(t_list **list, char **env)
// {
// 	t_list	*begin;

// 	begin = *list;
// 	while (begin)
// 	{
// 		if (ft_strncmp((const char *)begin->content, "echo", 4) == 0)
// 			printf("cat type\n");
// 		if (ft_strncmp((const char *)begin->content, "cd", 2) == 0)
// 			printf("cd type\n");
// 		if (ft_strncmp((const char *)begin->content, "pwd", 3) == 0)
// 			printf("pwd type\n");
// 		if (ft_strncmp((const char *)begin->content, "export", 6) == 0)
// 			printf("export type\n");
// 		if (ft_strncmp((const char *)begin->content, "unset", 5) == 0)
// 			printf("unset type\n");
// 		if (ft_strncmp((const char *)begin->content, "env", 3) == 0)
// 			printf("env type\n");
// 		if (ft_strncmp((const char *)begin->content, "exit", 4) == 0)
// 			printf("exit type\n");
// 		else
// 			non_buildin(*list, env, begin);
// 		// if (ft_parse = -1)
// 		// 	error("invalid programme input", -1);
// 		begin = begin->next;
// 	}
// 	begin = *list;
// }