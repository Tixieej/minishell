/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/11/30 17:52:31 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	prompt()
{
	write(1, "\033[38;5;105mminishell: \e[0m", 27);
}

int		main(int argc, char **argv)
{
	char	*line;
	int		result;
	char	*path;

	path = NULL;
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
		path = getcwd(char *buf, size_t size)
		//tokenizer aanroepen
		//andere dingen aanroepen
		
		while (result == 1)  // voorbeelde cat > test.txt
		{
			result = get_next_line(0, &line);
			// zet input om in linked lists die data opslaan
			free(line);
			line = NULL;
		}
		printf("%s\n", line); // zet data in structs
		free(line);
		line = NULL;
	}
	return (0);
}
