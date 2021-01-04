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
#include <signal.h>
int		send_signal (int pid)
{
        int ret;

		ret = kill(pid,SIGKILL);
		printf("sigkill : %d\n", SIGKILL);
        printf("ret : %d\n",ret);
		return(ret);
}


int		main(int argc, char **argv)
{
	pid_t	ret_value;
	char	*line;
	int		result;

	ret_value = 7;
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
		printf("ret_value2 %d\n", ret_value);
		printf("Child Process\n");
		printf("%s\n", argv[1]); //
		if (send_signal(ret_value) == 0)
			printf("childprocess is killed\n");
	}
	else
	{
		wait(NULL);
		printf("parent process\n"); //
	}
	return (0);
}
