/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:20:58 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/08 11:16:15 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig) // ctrl + c
{
	write(1, "\n", 1);
    prompt();
	(void)sig;
}
 
void handle_sigkill(int sig) // ctrl + d; niet quitten als je iets hebt geschreven, wel quitten als je niks hebt geschreven
{
	printf("exit %d\n", sig);
}

void	signal_handler(t_command *command)
{
	(void)command;
	signal(SIGINT, handle_sigint);
	signal(SIGKILL, handle_sigkill);
	signal(SIGQUIT, SIG_IGN);
}
