/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/21 12:29:55 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h> //
#include <unistd.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	pid_t	ret_value;
	char	*line;
	int		result;

	ret_value = 0;
	result = 1;
	line = NULL;
	if (argc != 2)
	{	
		printf("please give exactly one argument\n"); //
		return (1);
	}
	ret_value = fork();
	if (ret_value < 0)
		printf("creating childprocess had failed\n"); //
	else if (ret_value == 0)
	{
		ret_value = fork();
		printf("Child Process\n");
		printf("%s\n", argv[1]); //
	}
	else
	{
		wait(NULL);
		printf("parent process\n"); //
	}
	return (0);
}
