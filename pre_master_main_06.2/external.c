/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   external.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rdvrie <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by rixt          #+#    #+#                 */
/*   Updated: 2021/01/28 18:00:24 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**list_to_array(t_list **list)
{
	int		count;
	char	**array;
	int		i;
	t_list	*current;

	if (!(*list) || !((*list)->content))// klopt dit?
	{
		array = (char **)malloc(sizeof(char *));
		array[0] = NULL;
		return (array);
	}
	current = *list;
	count = 0;
	while (current)// misschien met list lopen maar dan met de kopie begin;
	{
		current = current->next; //
		count++;
	}
	array = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	current = *list;
	while (i < count)
	{
		array[i] = (char *)current->content;
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void			ft_exec(char *path, t_command cmd, char **env)
{
	pid_t	pid;
	char	**args;
	t_list	*arglist;

	arglist = cmd.args;
	ft_lstadd_front(&arglist, ft_create_elem(path));
	//in create_elem wordt gemalloct dus we moeten nog checken of dat gelukt is.
	//dat kunnen we toevoegen in create_elem zelf, of hieronder..
	args = list_to_array(&arglist);
	printf(" ft_exec: forken hieronder!\n");
	pid = fork();
	if (pid == 0)
		execve(path, args, env);
	else
		wait(NULL);
}

static void		with_path(t_command cmd, char **env)
{
	struct stat		buffer;
	char			*path;

	path = cmd.program;
	if (stat(path, &buffer) == 0)
		ft_exec(path, cmd, env);
	else
		printf("no such file or directory: %s\n", cmd.program);
}

static void		attach_path(t_command cmd, char **env)
{
	char		**paths;
	char		*path;
	struct stat	buffer;
	int			i;

	paths = make_path_array(env);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd.program);
		//cmd.args[0] = path;
		if (stat(path, &buffer) == 0)
		{
			ft_exec(path, cmd, env);
			break ;
		}
		i++;
	}
	if (stat(path, &buffer) != 0)
		printf("command not found: %s\n", cmd.program);
}


int			out_redirect(t_command *cmd)
{
	int		out_fd = 0;
	int		stdout_fd;

	//maak backup van originele fd = 0 en fd = 1 met dup
	// check of out_red bestaat
	stdout_fd = dup(STDOUT_FILENO);
	if (cmd->out_red)
	{
		if (stdout_fd < 0)
			printf("bouw hier error in!\n");
		out_fd = open(ft_lstlast(cmd->out_red)->content, O_CREAT | O_WRONLY, 0644);
		if(dup2(out_fd, STDOUT_FILENO) < 0)
		{
			printf("Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
	}
	return (stdout_fd);
}

int			in_redirect(t_command *cmd)
{
	int		in_fd = 0;
	int		stdin_fd;
	
	stdin_fd = dup(STDIN_FILENO);
	if (cmd->in_red)
	{
		if (stdin_fd < 0)
			printf("bouw hier error in!\n");
		in_fd = open(ft_lstlast(cmd->in_red)->content, O_RDONLY);
		if (dup2(STDIN_FILENO, in_fd) < 0)
		{
			printf("Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
	}
	return (stdin_fd);
}

void			external(t_command *cmd, char **env)
{
	int		stdout_fd;
	int		stdin_fd;

	stdout_fd = out_redirect(cmd);
	stdin_fd = in_redirect(cmd);
	if (ft_strchr(cmd->program, '/') != 0)
	{
		with_path(*cmd, env);
	}
	else
	{
		attach_path(*cmd, env);
	}
	if (dup2(STDOUT_FILENO, stdout_fd) < 0)
		{
			printf("Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
	if (dup2(STDIN_FILENO, stdin_fd) < 0)
		{
			printf("Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
}
