/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/14 12:23:13 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	parser(t_list **list)
{
	t_command		cmd;

	cmd.program = list[0]->content;//zou kunnen dat dit niet werkt nu **list
	cmd.args = ft_list_to_array(list);
	return (cmd);
}

void    	check_type(t_list **list, char **env)
{//deze krijgt t_command ipv t_list
	t_list	*begin;

	(void)env;
	begin = *list;
	while (begin)
	{
		if (ft_strncmp((const char *)begin->content, "cat", 3) == 0)
			printf("cat type\n");
		if (ft_strncmp((const char *)begin->content, "cp", 2) == 0)
			parser(list);
		if (ft_strncmp((const char *)begin->content, "echo", 4) == 0)
			printf("echo type\n");
		begin = begin->next;
	}
	begin = *list;
// als geen van de 7 builtins voldoet bij strcmp, stuur door naar de functie 'external'
}

