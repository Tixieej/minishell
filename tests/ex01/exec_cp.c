/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cp.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 14:10:28 by rixt          #+#    #+#                 */
/*   Updated: 2020/12/21 14:59:10 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int			main(void)
{
	char *const envp[0];
	char	*args[] = {"ft_split.c", "vla", NULL};
	
	execve("/bin/cp", args, envp);
	return (0);
}
