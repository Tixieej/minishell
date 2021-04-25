/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/21 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/06 13:22:56 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_string(t_command *command, char *s)
{
	t_list	*cur_args;
	char	*temp;
	int		n_check;

	cur_args = command->args;
	n_check = 0;
	temp = NULL;
	s = ft_strdup("");
	n_check = !ft_strncmp(cur_args->content, "-n", 2);
	if (n_check == 1)
		cur_args = cur_args->next;
	while (cur_args)
	{
		temp = ft_strjoin(s, (const char *)cur_args->content);
		free(s);
		s = ft_strjoin(temp, " ");
		free(temp);
		temp = NULL;
		cur_args = cur_args->next;
	}
	cur_args = command->args;
	if (ft_strlen(s) != 0 && n_check == 0)
		s[ft_strlen(s) - 1] = '\n';
	return (s);
}

void	echo(t_command *command, char *s)
{
	if (!command->args)
	{
		if (write(command->fd_out, "\n", 1) < 0)
			error_handler("write function failed\n", NULL, command, errno);
		return ;
	}
	s = create_string(command, s);
	if (write(command->fd_out, s, ft_strlen(s)) < 0)
		error_handler("write function failed\n", NULL, command, errno);
	free(s);
}
