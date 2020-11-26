/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 10:03:34 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/02/20 09:33:21 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int		main(void)
{
	int		fd1, fd2;
	char	*line;
	int		result;
	int		count;
	int		cur_fd;
	int		prev_result;

	fd1 = open("get_next_line.h", O_RDONLY);
	fd2 = open("get_next_line.c", O_RDONLY);
	//fd1 = 0;
	//fd2 = 0;
	result = 1;
	prev_result = 1;
	printf("fd1=%i en 2=%i\n", fd1, fd2);
	count = 0;
	while (result == 1 || prev_result == 1)
	{
		prev_result = result;
		cur_fd = (count % 2 == 0) ? fd1 : fd2;
		count++;
		result = get_next_line(cur_fd, &line);
		printf(" [%i][%i]--->| Line: [%s]\n", cur_fd, result, line);
		//if (line)
			free(line);
	}
	close(fd1);
	close(fd2);
	while(1);
	return (0);
}
