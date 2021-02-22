/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/15 11:31:56 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
static void			start_program(char **env)
{
	t_command	*command;
	t_list		*list;
	int			result;
	char		*line;
	// t_list		**begin;

	command = NULL;
	list = NULL;
	// begin = &list;
	result = 1;
	line = NULL;
	while (result == 1)
	{
		signal_handler(command);
		prompt();
		result = get_next_line(0, &line);
		if (result == -1)
		 	error_handler("get next line failed", list, NULL);
		if (line[0] == '\0')
			continue ;
		divide_input(&list, line, 0, 0);
		parser(&list, env, command);
		// t_command *cmd1;
		// t_command *cmd2;
		// ft_struct_push_back(&cmd1, "cat");
		// cmd1->args = ft_create_elem("Makefile");
		// cmd1->pipe_right = 1;
		// ft_struct_push_back(&cmd2, "grep");
		// cmd2->args = ft_create_elem("f");
		// cmd2->pipe_left = 1;
		// check_type(env, cmd1);
		// check_type(env, cmd2);
		ft_lstclear(&list, free);
		list = NULL;
		free(line);
		line = NULL;
	}
	exit(0);
}


int		main(int argc, char **argv, char **env)
{
	// t_list	*list;

	// list = NULL;
	(void)argv;
	if (argc != 1)
	{
		printf("no arguments needed");
		return (0);
	}
	start_program(env);
	return (0);
}
