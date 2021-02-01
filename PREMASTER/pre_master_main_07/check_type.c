/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 17:53:20 by rixt          #+#    #+#                 */
/*   Updated: 2021/01/28 17:54:26 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_type(t_list **list, char **env, t_command *command) //moet list wel mee?
{
	t_list		*cur_lst; //weg?
	t_command	*cur_struct;
	int			fd;

	//printf("check_type\n");
	cur_struct = command;
	cur_lst = *list; // weg?
	fd = redirection(command);
	// pipefunctie?
	if (ft_strncmp((const char *)cur_struct->program, "echo", 4) == 0)
		echo(command, fd);
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
