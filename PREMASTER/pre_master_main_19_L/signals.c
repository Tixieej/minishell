/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:20:58 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/22 19:49:09 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
