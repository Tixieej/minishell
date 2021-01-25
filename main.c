/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/21 10:00:51 by rixt          ########   odam.nl         */
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

int		main(int argc, char **argv, char **env)
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
	while (1)
	{
		//iets met signals? waarom hier?
		prompt();
		result = get_next_line(0, &line);
		//tokenizer aanroepen
		//andere dingen aanroepen
		printf("%s\n", line); //
		free(line);
	}
	return (0);
}
