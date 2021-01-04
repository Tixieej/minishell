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
#include <signal.h>


// Names of environment variables are case-sensitive and must not contain the character ‘=’. 
//System-defined environment variables are invariably uppercase. 
// The values of environment variables can be anything that can be represented as a string.
//A value must not contain an embedded null character, since this is assumed to terminate the string.

int		send_signal (int pid)
{
        int ret;

		ret = kill(pid,SIGKILL);
		printf("sigkill : %d\n", SIGKILL);
        printf("ret : %d\n",ret);
		return(ret);
}

void	prompt()
{
	write(1, "\033[38;5;105mhallo: \e[0m", 23);
}

int		main(int argc, char **argv)
{
	pid_t	ret_value;
	t_list 	*list;
	char	*line;
	int		result;

	ret_value = 1;
	result = 1;	
	list = NULL;
	line = NULL;
	(void)argv;
	if (argc != 1)
	{
		printf("no arguments needed"); //
		return (0);
	}
	//if  statement -> tweede arg is cat, cd etc doe dan ret_value
	ret_value = fork();
	if (ret_value < 0)
		printf("creating childprocess had failed\n"); //
	else if (ret_value == 0)
	{
		// ret_value = fork(); //twee keer prompt?
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
		while (list)  //prints list
		{
			printf("%s\n", (char*)list->data);
			printf("%p\n", (char*)list->next);
			list = list->next;
		}
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
