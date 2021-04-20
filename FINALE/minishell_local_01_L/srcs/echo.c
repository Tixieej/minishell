/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/21 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/20 17:00:29 by livlamin      ########   odam.nl         */
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


void	check_dol_val(t_command *command, char *end, char *start, int len)
{
	t_list	*cur_args;
	char	*mid;
	(void)end;

	mid = NULL;
	cur_args = command->args;
	while (cur_args)
	{
		len = 0;
		while (cur_args->content[len] != '\0')
		{
			if (cur_args->content[len] == '$' && cur_args->content[len + 1] == '?')
			{
				if (len > 0)
					start = ft_substr(cur_args->content, 0, len);
				end = ft_strdup(&cur_args->content[len + 2]);
				free(cur_args->content);
				if (start)
				{
					mid = ft_strjoin(start, ft_itoa(command->not_found));
					cur_args->content = ft_strjoin(mid, end);
				}		
				else
					cur_args->content = ft_strjoin(start, end);

				// if (mid)
					// len += ft_strlen(ft_itoa(command->not_found) - 1);
				// else
				printf("%d\n", len);
				free(start);
				free(mid);
				free(end);	
			}
			len++;
		}
		cur_args = cur_args->next;
	}
	cur_args = command->args;
}

void	echo(t_command *command, char *s)
{
	check_dol_val(command, NULL, NULL, 0);
	if (!command->args)
	{
		if (write(command->fd_out, "\n", 1) < 0)
			error_handler("write function failed\n", NULL, command, errno);
		return ;
	}
	s = create_string(command, s);
	if (write(command->fd_out, s, (ft_strlen(s))) < 0)
		error_handler("write function failed\n", NULL, command, errno);
	free(s);
}
