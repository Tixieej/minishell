/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/09 11:00:21 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/09 11:01:02 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			isnumber(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void		exit_func(t_command *cmd)
{
	int		num;
	int		argnum;

	num = 0;
	write(1, "exit\n", 5);
	argnum = ft_lstsize(cmd->args);
	if (argnum != 0)
	{
		if (isnumber(cmd->args->content) == 0)
		{
			printf("exit: %s: numeric argument required", cmd->args->content);
			num = 255;
		}
		else
		{
			if (argnum >= 2)
			{
				printf("exit: too many arguments\n");
				return ;
			}
			num = ft_atoi(cmd->args->content);
		}
	}
	exit(num);
}
