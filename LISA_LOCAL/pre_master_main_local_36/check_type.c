/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 17:53:20 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/02 11:53:53 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	check_type_two(char **env, t_command *command, pid_t process)
{
	printf("check type 2\n");
	t_command	*cur_struct;

	cur_struct = command;
	if (ft_strncmp((const char *)cur_struct->program, "echo", 5) == 0)
		echo(command);
	else if (ft_strncmp((const char *)cur_struct->program, "cd", 3) == 0)
		cd(command, env);
	else if (ft_strncmp((const char *)cur_struct->program, "pwd", 4) == 0)
		pwd(command);
	else if (ft_strncmp((const char *)cur_struct->program, "env", 4) == 0)
		env_check(command, env);
	else if (ft_strncmp((const char *)cur_struct->program, "export", 6) == 0)
		printf("export type\n");
	else if (ft_strncmp((const char *)cur_struct->program, "unset", 6) == 0)
		printf("unset type\n");
	else if (ft_strncmp((const char *)cur_struct->program, "exit", 5) == 0)
		exit_func(command);
	else
	{
		// dup_func(command);
		external(command, env, process);
	}
	return ;
}

void	check_type(char **env, t_command *command)
{
	t_command	*cur_struct;
	pid_t		process;

	cur_struct = command;
	process = -1;
	if (redirection(cur_struct) == -1)
		return;
	if (command->pipe_right == 1 || command->pipe_left == 1)
		process = pipes(env, cur_struct);
	else
		check_type_two(env, command, process);
}
