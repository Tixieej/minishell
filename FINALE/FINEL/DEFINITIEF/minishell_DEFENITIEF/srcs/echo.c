/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/21 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/23 22:04:42 by livlamin      ########   odam.nl         */
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

static char	*enter_dol(t_list *cur_args, t_command *command, size_t *start)
{
	char	*str_start;
	char	*str_end;
	char	*str_temp;
	char	*not_found;

	str_start = NULL;
	str_end = NULL;
	str_temp = NULL;
	not_found = ft_itoa(command->not_found);
	if (*start > 0)
		str_start = ft_substr(cur_args->content, 0, *start);
	else
		str_start = ft_strdup("");
	if ((*start + 2) < ft_strlen(cur_args->content))
		str_end = ft_strdup(&cur_args->content[*start + 2]);
	else
		str_end = ft_strdup("");
	str_temp = ft_strjoin(str_start, not_found);
	free(cur_args->content);
	cur_args->content = ft_strjoin(str_temp, str_end);
	free(str_start);
	free(str_end);
	free(str_temp);
	free(not_found);
	return (cur_args->content);
}

static void	check_dollar(t_command *command)
{
	t_list	*cur_args;
	size_t	start;

	cur_args = command->args;
	start = 0;
	while (cur_args)
	{
		start = 0;
		while (cur_args->content[start] != '\0')
		{
			if (cur_args->content[start] == '$'
				&& cur_args->content[start + 1] == '?')
				cur_args->content = enter_dol(cur_args, command, &start);
			start++;
		}
		cur_args = cur_args->next;
	}
	cur_args = command->args;
}

void	echo(t_command *command, char *s)
{
	check_dollar(command);
	if (!command->args)
	{
		if (write(command->fd_out, "\n", 1) < 0)
			error_handler("write function failed\n", NULL, command, 0);
		return ;
	}
	s = create_string(command, s);
	if (write(command->fd_out, s, (ft_strlen(s))) < 0)
		error_handler("write function failed\n", NULL, command, 0);
	free(s);
}
