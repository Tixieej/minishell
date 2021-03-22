/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/12/01 15:55:26 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *str, int ret)
{
	printf("%s\n", str);
	if (ret < 0)
		exit(-1);
}

void    check_type(t_list **list, char **env)
{
	t_list	*begin;

	begin = *list;
	while (begin)
	{
		make struct;
		if (ft_strncmp((const char *)begin->content, "echo", 4) == 0)
			printf("cat type\n");
		if (ft_strncmp((const char *)begin->content, "cd", 2) == 0)
			printf("cd type\n");
		if (ft_strncmp((const char *)begin->content, "pwd", 3) == 0)
			printf("pwd type\n");
		if (ft_strncmp((const char *)begin->content, "export", 6) == 0)
			printf("export type\n");
		if (ft_strncmp((const char *)begin->content, "unset", 5) == 0)
			printf("unset type\n");
		if (ft_strncmp((const char *)begin->content, "env", 3) == 0)
			printf("env type\n");
		if (ft_strncmp((const char *)begin->content, "exit", 4) == 0)
			printf("exit type\n");
		else
			ft_parse(*list, env, begin);
		// if (ft_parse = -1)
		// 	error("invalid programme input", -1);
		begin = begin->next;
	}
	begin = *list;
}


while(begin)
{
	voer uit als bestaand ding
	begin ;
	begin overnieu
}

