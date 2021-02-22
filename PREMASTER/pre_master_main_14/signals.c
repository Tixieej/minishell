/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:20:58 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/22 15:40:34 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigkill(int sig) // ctrl + d; niet quitten als je iets hebt geschreven, wel quitten als je niks hebt geschreven
{
	printf("exit %d\n", sig);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
    	prompt();
	}

	if (sig == SIGQUIT)
		write (1, "\b\b  \b\b", 6);
}
