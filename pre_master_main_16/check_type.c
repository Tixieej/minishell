/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 17:53:20 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/02 09:51:27 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	check_type_two(char **env, t_command *command, pid_t process)
{
	t_command	*cur_struct;

	cur_struct = command;
	if (ft_strncmp((const char *)cur_struct->program, "echo", 4) == 0)
		echo(command);
	else if (ft_strncmp((const char *)cur_struct->program, "cd", 2) == 0)
		cd(command, env);
	else if (ft_strncmp((const char *)cur_struct->program, "pwd", 3) == 0)
		pwd(command);
	else if (ft_strncmp((const char *)cur_struct->program, "export", 6) == 0)
		export_func(command, env);
	else if (ft_strncmp((const char *)cur_struct->program, "unset", 5) == 0)
		unset(command, &env);
	else if (ft_strncmp((const char *)cur_struct->program, "env", 3) == 0)
		printf("env type\n");
	else if (ft_strncmp((const char *)cur_struct->program, "exit", 4) == 0)
		exit_func(command);
	else
	{
		// dup_func(command);
		external(command, env, process);
	}
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
