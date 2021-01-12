/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:37:52 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/12 09:08:37 by rixt          ########   odam.nl         */
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

//CHECK OF ER IN list[0] EEN / VOORKOMT DAN IS HET AL EEN PATH, DUS DAN MOET ENV ER NIET VOORGEPLAKT WORDEN	

int			main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		result;
	t_list	*cp;
	char	**paths;
	struct	stat buffer;
	char	*path;

	result = 1;
	(void)argv;
	(void)argc;

	/* dit deel doet lisa: tokenizen */
	cp = ft_create_elem("cp");
	ft_list_push_back(&cp, "testfile");
	ft_list_push_back(&cp, "vla");
	/* struct maken */
	t_command cp_command;
	ft_make_struct(cp, &cp_command);
	

	if (ft_strchr(cp_command.program, '/') != 0)
	{
		path = cp_command.program;
		if (stat(path, &buffer) == 0)
		{
			pid = fork();
				if (pid == 0)
					execve(path, cp_command.args, envp);
				else
					wait(NULL);
		}
	}
	else
	{
		paths = make_path_array(envp);
		int i = 0;

		while (paths[i])
		{
			path = ft_strjoin(paths[i], "/");
			path = ft_strjoin(path, cp_command.program);
			cp_command.args[0] = path;
			printf("%s\n", cp_command.args[0]);
			if (stat(path, &buffer) == 0)
			{
				pid = fork();
					if (pid == 0)
						execve(path, cp_command.args, envp);
					else
						wait(NULL);
				break;// uit de while loop.
			}
			i++;
		}
	}
	return (0);
}
