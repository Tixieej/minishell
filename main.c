/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/11/26 10:35:26 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h> //
#include <unistd.h>

int		main(int argc, char **argv)
{
	pid_t ret_value;

	ret_value = fork();
	if (ret_value < 0)
		printf("creating childprocess had failed\n"); //
	if (ret_value == 0 && argc > 1)
	{
		printf("%s\n", argv[1]); //
	}
	else
	{
		wait(NULL);
		printf("parent process\n"); //
	}
	return (0);
}
