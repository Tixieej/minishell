/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rdvrie <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by rixt          #+#    #+#                 */
/*   Updated: 2021/01/23 12:23:35 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**list_to_array(t_list **list)
{
	int		count;
	char	**array;
	int		i;
	t_list	*current;

	printf("list_to_array\n");
	if (!(*list) || !((*list)->content))// klopt dit?
	{
		array = (char **)malloc(sizeof(char *));
		array[0] = NULL;
		return (array);
	}
	current = *list;
	count = 0;
	while (current) // misschien met list lopen maar dan met de kopie begin;
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

void		ft_exec(char *path, t_command cmd, char **env)
{
	pid_t	pid;
	char	**args;
	t_list	*arglist;

	printf("ft_exec\n");
	arglist = cmd.args;
	ft_lstadd_front(&arglist, ft_create_elem(path));
	//in create_elem wordt gemalloct dus we moeten nog checken of dat gelukt is.
	//dat kunnen we toevoegen in create_elem zelf, of hieronder..
	args = list_to_array(&(cmd.args));
	printf(" ft_exec: forken hieronder!\n");
	pid = fork();
	if (pid == 0)
		execve(path, args, env);
	else
		wait(NULL);
}

void		with_path(t_command cmd, char **env)
{
	struct stat		buffer;
	char			*path;

	path = cmd.program;
	//paths = ft_split(path, ' ');
	if (stat(path, &buffer) == 0)
		ft_exec(path, cmd, env);
	else
		printf("no such file or directory: %s\n", cmd.program);
}

void		attach_path(t_command cmd, char **env)
{
	char		**paths;
	char		*path;
	struct stat	buffer;
	int			i;

	printf("attach_path\n");
	paths = make_path_array(env);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd.program);
		//cmd.args[0] = path;
		//printf("%s\n", cmd.args[0]);
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

void		external(t_command *cmd, char **env)
{
	printf("external\n");
	if (ft_strchr(cmd->program, '/') != 0)
	{
		with_path(*cmd, env);
	}
	else
	{
		attach_path(*cmd, env);
	}
}
