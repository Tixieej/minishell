/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 17:53:20 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/11 12:45:48 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	check_type_two(char ***env, t_command *command, pid_t process)
{
	t_command	*cur_struct;

	cur_struct = command;
	if (ft_strncmp((const char *)cur_struct->program, "echo", 5) == 0)
		echo(command, NULL);
	else if (ft_strncmp((const char *)cur_struct->program, "cd", 3) == 0)
		cd(command, *env, 0, NULL);
	else if (ft_strncmp((const char *)cur_struct->program, "pwd", 4) == 0)
		pwd(command);
	else if (ft_strncmp((const char *)cur_struct->program, "env", 4) == 0)
		env_check(command, *env, 0);
	else if (ft_strncmp((const char *)cur_struct->program, "export", 7) == 0)
		export_func(command, env);
	else if (ft_strncmp((const char *)cur_struct->program, "unset", 6) == 0)
		unset(command, env);
	else if (ft_strncmp((const char *)cur_struct->program, "exit", 5) == 0)
		exit_func(command);
	else
		external(command, *env, process);
	return ;
}

void	check_type(char ***env, t_command *command)
{
	t_command	*cur_struct;
	pid_t		process;

	cur_struct = command;
	process = -1;
	if (redirection(cur_struct) == -1)
		return ;
	if (command->pipe_right == 1 || command->pipe_left == 1)
		process = pipes(env, cur_struct, 0, 0);
	else
		check_type_two(env, command, process);
}
