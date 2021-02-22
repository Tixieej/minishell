/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 17:53:20 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/11 13:45:12 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void    dup_func(t_command *command)
// {
//     if (dup2(command->fd_out, STDOUT_FILENO) < 0)
//     {
// 	    printf("Unable to duplicate file descriptor.");
// 	    exit(EXIT_FAILURE);
//     }
//     if (dup2(command->fd_in, STDIN_FILENO) < 0)
//     {
// 	    printf("Unable to duplicate file descriptor.");
// 	    exit(EXIT_FAILURE);
//     }
// }

void	check_type(char **env, t_command *command)
{
	t_command	*cur_struct;
	int			process;

	cur_struct = command;
	redirection(cur_struct);
	process = -1;
	if (command->pipe_right == 1 || command->pipe_left == 1)
		process = pipes(cur_struct);
	if (ft_strncmp((const char *)cur_struct->program, "echo", 4) == 0)
		echo(command);
	else if (ft_strncmp((const char *)cur_struct->program, "cd", 2) == 0)
		cd(command, env, NULL);
	else if (ft_strncmp((const char *)cur_struct->program, "pwd", 3) == 0)
		pwd(command->fd_out);
	else if (ft_strncmp((const char *)cur_struct->program, "export", 6) == 0)
		printf("export type\n");
	else if (ft_strncmp((const char *)cur_struct->program, "unset", 5) == 0)
		printf("unset type\n");
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
