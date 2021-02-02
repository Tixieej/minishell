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

pid_t	pipes(t_command *cmd)
{
	int     fd[2];
	pid_t   process;

	pipe(fd);
	if ((process = fork()) == -1) // check of fork lukt
	{
		perror("fork");
		exit(1);
	}
	if (process == 0) // Child process
	{
		printf("pipe child process\n");
		if (cmd->pipe_right != 1)
		{
			printf("no pipe on right side\n");
			close(fd[1]); // sluit schrijfkant af
		}
		if (cmd->pipe_left != 1)
		{
			printf("no pipe on left side\n");
			close(fd[0]); // sluit leeskant af
		}
	}
	else
	{
		/* Parent process */
		wait(NULL);
		printf("pipe parent process\n");
		//close(fd[1]);
	}
	return (process);
}

void	check_type(t_list **list, char **env, t_command *command) //moet list wel mee?
{
	t_list		*cur_lst; //weg?
	t_command	*cur_struct;
	int			fd;
	int			process;

	/* dit is een check en kan later weg */
	printf("check_type\n");
	t_list *begin = command->args;
	while ((command->args))
	{
		printf("\targs: [%s]\n", (command->args)->content);
		command->args = command->args->next;
	}
	command->args = begin;
	/* einde check */

	cur_struct = command;
	cur_lst = *list; // weg?
	fd = redirection(cur_struct);
	// pipefunctie?
	process = -1;
	if (command->pipe_right == 1 || command->pipe_left == 1)
		process = pipes(cur_struct);
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
		external(command, env, fd, process);
		// if (non_builtin = -1)
		// 	error("invalid programme input", -1);
}
