/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   external.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rdvrie <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by rixt          #+#    #+#                 */
/*   Updated: 2021/04/05 14:25:38 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(char *path, t_command *cmd, t_list *arglist, char **env)
{
	char	**args;

	args = list_to_array(arglist);
	if (execve(path, args, env) == -1)
	{
		command_not_found(cmd, cmd->program, "is a directory", 126);
		free_array(args);
		exit(126);
	}
}

void	ft_exec(char *path, t_command *cmd, char **env, pid_t process)
{
	t_list	*arglist;
	t_list	*new_elem;

	arglist = cmd->args;
	new_elem = ft_create_elem(path);
	if (!new_elem)
		error_handler("malloc failed", NULL, cmd, 1);
	ft_lstadd_front(&arglist, new_elem);
	if (process == -1)
		process = fork();
	if (process == 0)
		child(path, cmd, arglist, env);
	else
		wait(NULL);
	free(new_elem);
}

static void	dup_back(t_command *cmd)
{
	if (cmd->out_red)
	{
		dprintf(2, "\t\t fuck \n");
		if (dup2(cmd->stdout_backup, STDOUT_FILENO) < 0)
		{
			write(2, "Unable to duplicate file descriptor.\n", 37);
			exit(9);
		}
		close(cmd->stdout_backup);
	}
	if (cmd->in_red)
	{

		if (dup2(cmd->stdin_backup, STDIN_FILENO) < 0)
		{
			write(2, "Unable to duplicate file descriptor.\n", 37);
			exit(9);
		}
		close(cmd->stdin_backup);
	}
}

void	external(t_command *cmd, char **env, pid_t process)
{
	cmd->stdout_backup = out_redirect(cmd);// hier veranderd fd_out, maar dit is niet hoe het hoort volgens mij rixt, want
	// jij gebruikt het hier volgens mij als backup voor de redirection, maar het moet de fd zijn van de file, maar dat is toch ... hmmm
	// op zich is dat ook niet verkeerd, jawel. ik dacht dat dup2 anders werkte. dat je ze wisselde, maar dat is niet zo.
	// je opent file1, fd_in wordt de fd daarvan, dan dup2 je stdin, dat word een andere fd, bijv 5,
	// die moet je ergens anders opslaan. dan gaat het misschien wel goed.
	cmd->stdin_backup = in_redirect(cmd);
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return ;
	write(2, "\t=== external ===\n", ft_strlen("\t=== external ===\n"));
	print_cur_struct(cmd);
	if (ft_strchr(cmd->program, '/') != 0)
		with_path(cmd, env, process);
	else
		without_path(cmd, env, process);
	dup_back(cmd);
	write(2, "\t=== na dup_back ===\n", ft_strlen("\t=== na dup_back ===\n"));
	print_cur_struct(cmd);
}
