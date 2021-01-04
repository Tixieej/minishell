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
#include "ft_list.h"


// Names of environment variables are case-sensitive and must not contain the character ‘=’. 
//System-defined environment variables are invariably uppercase. 
// The values of environment variables can be anything that can be represented as a string.
//A value must not contain an embedded null character, since this is assumed to terminate the string. 
void	prompt()
{
	write(1, "\033[38;5;105mhallo: \e[0m", 23);
}


void	divide_input()
{
	int result;
	char	*line;

	result = 1;
	line == NULL;
	while (result == 1)
	{
		//iets met signals? waarom hier?
		prompt();
		result = get_next_line(0, &line);
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
	// while (list)
	// {
	// 	printf("%s\n", (char*)list->data);
	// 	printf("%p\n", (char*)list->next);
	// 	list = list->next;
	// }
}

void compare_input(t_list *list)
{
	if (ft_strncmp(list->data , "cat", 3)
		printf("cat type");
}
int		main(int argc, char **argv, char *envp[])
{
	t_list *list;
	
	list = NULL;
	(void)argv;
	if (argc != 1)
	{
		printf("no arguments needed"); //
		return (0);
	}
	compare_input(list);

	return (0);
}
