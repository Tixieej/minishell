/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/14 11:14:04 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_list_to_array(t_list *list)
{
	int		count;
	char	**array;
	int		i;
	t_list	*begin;

	begin = list;
	count = 0;
	while (list)
	{
		list = list->next;
		count++;
	}
	array = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	list = begin;
	while (i < count)
	{
		array[i] = (char *)list->content;
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void		ft_exec(char *path, t_command cp_command, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execve(path, cp_command.args, envp);
	else
		wait(NULL);
}

void		with_path(t_command cmd, char **envp)
{
	struct stat		buffer;
	char			*path;

	path = cmd.program;
	//paths = ft_split(path, ' ');
	if (stat(path, &buffer) == 0)
		ft_exec(path, cmd, envp);
	else
		printf("no such file or directory: %s\n", cmd.program);
}

void		attach_path(t_command cmd, char **envp)
{
	char		**paths;
	char		*path;
	struct stat	buffer;
	int			i;

	paths = make_path_array(envp);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd.program);
		cmd.args[0] = path;
		printf("%s\n", cmd.args[0]);
		if (stat(path, &buffer) == 0)
		{
			ft_exec(path, cmd, envp);
			break ;
		}
		i++;
	}
	if (stat(path, &buffer) != 0)
		printf("command not found: %s\n", cmd.program);
}

void		ft_parse(t_list *list, char **envp)
{
	t_command		cmd;

	cmd.program = list[0].content;
	cmd.args = ft_list_to_array(list);
	/* parse.c komt boven check_type functie, code hieronder komt in andere functie en wordt aangeroepen aan het eind van check_type*/
	if (ft_strchr(cmd.program, '/') != 0)
	{
		with_path(cmd, envp);
	}
	else
	{
		attach_path(cmd, envp);
	}
}
