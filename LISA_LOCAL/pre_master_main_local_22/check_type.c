/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 17:53:20 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/09 10:44:14 by livlamin      ########   odam.nl         */
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
	t_command	**cur_struct;
	int			process;

	cur_struct = &command;
	printf("p comd: %p\n", command);
	printf("check_type");
	print_cur_struct(*cur_struct);
	redirection(command);
	(void)env;

	// printf("\targs: [%s]\n", ((*cur_struct)->args)->content);
	
	print_cur_struct(command);
	// printf("check type args: %s\n", (char *)(cur_struct)->args);
	process = -1;
	if (command->pipe_right == 1 || command->pipe_left == 1)
		process = pipes(command);
	if (ft_strncmp((const char *)command->program, "echo", 4) == 0)
		echo(command);
	// else if (ft_strncmp((const char *)command->program, "cd", 2) == 0)
	// 	cd(command, env, NULL);
	// else if (ft_strncmp((const char *)command->program, "pwd", 3) == 0)
	// 	pwd(command->fd_out);
	// else if (ft_strncmp((const char *)command->program, "export", 6) == 0)
	// 	printf("export type\n");
	// else if (ft_strncmp((const char *)command->program, "unset", 5) == 0)
	// 	printf("unset type\n");
	// else if (ft_strncmp((const char *)command->program, "env", 3) == 0)
	// 	printf("env type\n");
	// else if (ft_strncmp((const char *)command->program, "exit", 4) == 0)
	// 	printf("exit type\n");
	// else
	// {
	// 	dup_func(command);
	// 	external(command, env, command->fd_out, process);
	// }
}


// void	check_type(char **env, t_command *command)
// {
// 	t_command	*cur_struct;
// 	int			process;

// 	cur_struct = command;
// 	redirection(cur_struct);
// 	// printf("\techo args: [%s]\n", ((*cur_struct)->args)->content);
// 	// printf("\techo args: [%s]\n", ((command)->args)->content);
// 	// printf("check type args: %s\n", (char *)(cur_struct)->args);
// 	process = -1;
// 	if (command->pipe_right == 1 || command->pipe_left == 1)
// 		process = pipes(cur_struct);
// 	if (ft_strncmp((const char *)cur_struct->program, "echo", 4) == 0)
// 		echo(command);
// 	else if (ft_strncmp((const char *)cur_struct->program, "cd", 2) == 0)
// 		cd(command, env, NULL);
// 	else if (ft_strncmp((const char *)cur_struct->program, "pwd", 3) == 0)
// 		pwd(command->fd_out);
// 	else if (ft_strncmp((const char *)cur_struct->program, "export", 6) == 0)
// 		printf("export type\n");
// 	else if (ft_strncmp((const char *)cur_struct->program, "unset", 5) == 0)
// 		printf("unset type\n");
// 	else if (ft_strncmp((const char *)cur_struct->program, "env", 3) == 0)
// 		printf("env type\n");
// 	else if (ft_strncmp((const char *)cur_struct->program, "exit", 4) == 0)
// 		printf("exit type\n");
// 	else
// 	{
// 		dup_func(command);
// 		external(command, env, command->fd_out, process);
// 	}
// }
