/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/21/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/21/01 15:55:26 by livlamin          ########   odam.nl     */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_type(t_list **list, char **env, t_command *command) //moet list wel mee?
{
	t_list		*cur_lst;
	t_command	*cur_struct;

	cur_struct = command;
	cur_lst = *list;
    (void)env;
	if (ft_strncmp((const char *)cur_struct->program, "echo", 4) == 0)
		echo(command);
	else if (ft_strncmp((const char *)cur_struct->program, "cd", 2) == 0)
		cd(command);
	else if (ft_strncmp((const char *)cur_struct->program, "pwd", 3) == 0)
		printf("pwd type\n");
	else if (ft_strncmp((const char *)cur_struct->program, "export", 6) == 0)
		printf("export type\n");
	else if (ft_strncmp((const char *)cur_struct->program, "unset", 5) == 0)
		printf("unset type\n");
	else if (ft_strncmp((const char *)cur_struct->program, "env", 3) == 0)
		printf("env type\n");
	else if (ft_strncmp((const char *)cur_struct->program, "exit", 4) == 0)
		printf("exit type\n");
	else
		external(command, env);
		// if (non_builtin = -1)
		// 	error("invalid programme input", -1);
}
