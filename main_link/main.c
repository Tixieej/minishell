/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/11/26 15:55:26 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h> //
#include <unistd.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

void	prompt()
{
	write(1, "\033[38;5;105mhallo: \e[0m", 23);
}

int		main(int argc, char **argv)
{
	char	*line;
	int		result;

	result = 1;
	line = NULL;
	(void)argv;
	if (argc != 1)
	{
		printf("no arguments needed"); //
		return (0);
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
		// list = ft_create_elem(line);
		ft_list_push_back(&list, line);
		// printf("%s\n",list->data);
		// printf("%p\n",list->next);
		// list = list->next;

		// path = getcwd(char *buf, size_t size)
		//tokenizer aanroepen
		//andere dingen aanroepen
		
		// while (result == 1)  // voorbeelde cat > test.txt
		// {
		// 	result = get_next_line(0, &line);
		// 	// zet input om in linked lists die data opslaan
		// 	ft_list_push_back(&list, line);
		// 	// printf("%s\n",list->data);
		// 	// printf("%p\n",list->next);
		// 	list = list->next;
		// 	free(line);
		// 	line = NULL;
		// }
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	while (list)
	{
		printf("%s\n", (char*)list->data);
		printf("%p\n", (char*)list->next);
		list = list->next;
	}
	return (0);
}
	// while (1)
	// {
	// 	//iets met signals? waarom hier?
	// 	prompt();
	// 	result = get_next_line(0, &line);
	// 	//tokenizer aanroepen
	// 	//andere dingen aanroepen
	// 	printf("%s\n", line); //
	// 	free(line);
	// }
	return (0);
}
