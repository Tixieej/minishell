/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/25 13:43:37 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
static void			start_program(char **env)
{
	t_command	*command;
	t_list		*list;
	int			result;
	char		*line;

	command = NULL;
	list = NULL;
	result = 1;
	line = NULL;
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	while (result == 1)
	{
		prompt();
		result = get_next_line(0, &line);
		if (result == -1)
		 	error_handler("get next line failed", list, NULL);
		if (line[0] == '\0')
			continue ;
		divide_input(&list, line, 0, 0);
		parser(&list, env, command);
		ft_lstclear(&list, free);
		list = NULL;
		free(line);
		line = NULL;
	}
	exit(0);//exit met 0 ?
}

int		main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
	{
		printf("no arguments needed");
		return (0);
	}
	start_program(env);
	return (0);
}
