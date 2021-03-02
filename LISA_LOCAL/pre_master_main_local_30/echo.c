/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/21 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/02 10:57:16 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		echo(t_command *command)
{
	t_list      *cur_args;
	char        *s;
	int         n_check;
	
	if (!command->args) // dubbelcheck later
		return;
	cur_args = command->args;
	s = ft_strdup("");
	n_check = !ft_strncmp(cur_args->content, "-n", 2);
	if (n_check == 1)
		cur_args = cur_args->next;
	while (cur_args)
	{
		s = ft_strjoin(s, (const char *)cur_args->content);
		s = ft_strjoin(s, " ");
		cur_args = cur_args->next;
	}
	if (ft_strlen(s) == 0 && n_check == 0)
			s = ft_strdup("\n");
	if (ft_strlen(s) != 0 && n_check == 0)
		s[ft_strlen(s) - 1] = '\n';
	// if (write(command->fd_out, s, ft_strlen(s)) < 0)
	// 	printf("error\n");
	if (write(STDOUT_FILENO, s, ft_strlen(s)) < 0)
		printf("error\n");
	free(s);
}
