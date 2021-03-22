/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/11/30 15:07:14 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"
<<<<<<< HEAD:troep/main_org.c
=======
#include <fcntl.h>
#include <stdlib.h>
#include "ft_list.h"
>>>>>>> 3be00f8a812802319fd8cf898d7b5c78ad549cd3:LV_tests/linked_list_met_str/main.c

void	prompt()
{
	write(1, "\033[38;5;105mminishell: \e[0m", 27);
}

int		main(int argc, char **argv)
{
	t_list *list;
	char	*line;
	int		result;
	
	list = NULL;
	result = 1;
	line = NULL;
	(void)argv;
	if (argc != 1)
	{
		printf("no arguments needed"); //
		return (0);
	}
	while (result == 1)
	{
		//iets met signals? waarom hier?
		prompt();
		result = get_next_line(0, &line);
<<<<<<< HEAD:troep/main_org.c
		//tokenizer aanroepen
		//andere dingen aanroepen
		
		while (result == 1)  // voorbeelde cat > test.txt
		{
			result = get_next_line(0, &line);
			free(line);
			line = NULL;
		}
		printf("%s\n", line); // zet data in structs
		free(line);
		line = NULL;
=======
		ft_list_push_back(&list, line);
		while (result == 1)  // voorbeelde cat > test.txt
		{
			result = get_next_line(0, &line);
			ft_list_push_back(&list, line);
		}
		// free(line);
		// line = NULL;
	}
	free(line);
	line = NULL;
	while (list)
	{
		printf("%s\n", (char*)list->data);
		printf("%p\n", (char*)list->next);
		list = list->next;
>>>>>>> 3be00f8a812802319fd8cf898d7b5c78ad549cd3:LV_tests/linked_list_met_str/main.c
	}
	return (0);
}
