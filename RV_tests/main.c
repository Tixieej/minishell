/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:37:52 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/12 14:43:53 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdio.h> //printf
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h> //write
#include "minishell.h"
#include <sys/stat.h> //stat

void		prompt(void)
{
	write(1, "\033[38;5;105mlrsh$ \e[0m", 22);
}

void		ft_make_struct(t_list *list, t_command *cmd)
{
	cmd->program = list[0].data;
	cmd->args = ft_list_to_array(list);
	printf("struct: %s, args[1]: %s args[2]: %s\n", cmd->program, cmd->args[1], cmd->args[2]);
}

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
		array[i] = (char *)list->data;
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void		ft_exec(char *path, t_command cp_command, char **envp)
{//miss kan if(stat(path, &buffer) == 0) hier ook naar verplaatst worden, maar dan moet je dus een int returnen die aangeeft of de program wel of niet bestaat. dus gewoon returnen wat stat returnt? En errorhandling regelen ofc
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execve(path, cp_command.args, envp);
	else
		wait(NULL);
}

int			main(int argc, char **argv, char **envp)
{
	int			result;
	t_list		*cp;
	char		**paths;
	char		*path;
	struct		stat buffer;
	t_command	cp_command;
	int			i;

	result = 1;
	(void)argv;
	(void)argc;

	/* dit deel doet lisa: tokenizen */
	cp = ft_create_elem("onzin");
	ft_list_push_back(&cp, "testfile");
	ft_list_push_back(&cp, "vla");
	/* struct maken */
	ft_make_struct(cp, &cp_command);
	
	if (ft_strchr(cp_command.program, '/') != 0)
	{
		path = cp_command.program;
		paths = ft_split(path, ' ');//gewoon alleen path
		if (stat(path, &buffer) == 0)
			ft_exec(path, cp_command, envp);
		else
			printf("no such file or directory: %s\n", cp_command.program);
	}
	else
	{
		paths = make_path_array(envp);
		i = 0;
		while (paths[i])
		{
			path = ft_strjoin(paths[i], "/");
			path = ft_strjoin(path, cp_command.program);
			cp_command.args[0] = path;
			printf("%s\n", cp_command.args[0]);
			if (stat(path, &buffer) == 0)
			{
				ft_exec(path, cp_command, envp);
				break;
			}
			i++;
		}
		if (stat(path, &buffer) != 0)//als niet gevonden
			printf("command not found: %s\n", cp_command.program);
	}
	ft_exec(path, cp_command, envp);
	return (0);
}
