/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/11/26 13:24:06 by rixt          ########   odam.nl         */
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

	if (argc != 2)
	{	
		printf("please give exactly one argument\n");
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
		int		fd;
		char	*line;
		int		result;

		fd = 0;
		result = 1;
		while (result == 1)
		{
			result = get_next_line(fd, &line);
		}
	}
	return (0);
}
