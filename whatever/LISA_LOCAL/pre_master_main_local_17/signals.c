/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:20:58 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/04 17:34:22 by rixt          ########   odam.nl         */
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
