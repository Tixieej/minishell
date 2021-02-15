/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/08 14:08:37 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
 
static void			start_program(t_list *list, char **env)
{
	int			result;
	char		*line;
	t_list		**begin;
	t_command	*command;
	command = NULL;
	begin = &list;
	result = 1;
	line = NULL;
	while (result == 1)
	{
		signal_handler(command);
		prompt();
		result = get_next_line(0, &line);
		// if (result == -1) //check inbouwen?
		if (line[0] == '\0') //als je gelijk op enter drukt, terug naar begin while loop
			continue ;
		divide_input(&list, line, 0, 0);
		parser(&list, env, command);
		// while ((*begin))// loop om te lezen wat er gebeurt, later weghalen
		// {
		// 	printf("list item: [%s]\n", (char*)((*begin)->content));
		// 	// printf("begin adress: %p\n", begin);
		// 	begin = &(*begin)->next;
		// }
		ft_lstclear(&list, free);
		list = NULL;
		// begin = &list;
		free(line);
		line = NULL;
	}
	ft_lstclear(&list, free);
	exit(0);
}


int		main(int argc, char **argv, char **env)
{
	t_list	*list;

	list = NULL;
	(void)argv;
	if (argc != 1)
	{
		printf("no arguments needed");
		return (0);
	}
	start_program(list, env);
	return (0);
}