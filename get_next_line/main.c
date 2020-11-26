/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 16:57:03 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/11/26 13:01:43 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int		main(void)
{
	int		fd;
	char	*line;
	int		result;

	//fd = open("get_next_line.h", O_RDONLY);
	fd = 0;
	//fd = 42000;
	result = 1;
	while (result == 1)
	{
		result = get_next_line(fd, &line);
		printf(" [%i]--->| Line: %s\n", result, line);
		//if (line)
		//	free(line);
	}
	return (0);
}
