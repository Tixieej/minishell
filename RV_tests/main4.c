/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:37:52 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/11 12:53:58 by rixt          ########   odam.nl         */
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
/*
char		*ft_appendpath1(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (join == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	join[i] = '/';
	i++;
	while (s2[j] != '\0')
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
*/

char		*ft_append_path(char *str)
{

//CHECK OF ER IN list[0] EEN / VOORKOMT DAN IS HET AL EEN PATH, DUS DAN MOET ENV ER NIET VOORGEPLAKT WORDEN	

	char *path = "/bin/";
	return (ft_strjoin(path, str));
}

void		ft_execute(char **command, char **envp)
{
	char	*path;

	path = ft_append_path(command[0]);
	execve(path, command, envp);
}

int			main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		result;
	t_list	*cp;
	//t_list	*echo;
	//t_list	*wrong;
	char	**paths;
	struct	stat buffer;

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


	/*	maak paths array, splits PATH var en stop die erin
	**	for path in paths, plak cmd->program erachter en gooi in stat
	**	als stat 0 teruggeeft, fork, in child execve(path)
	*/	
	paths = make_path_array(envp);
	/* check of pad bestaat */
	int i = 0;
	while (paths[i])
	{
		char *path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cp_command.program);
		printf("%s\n", path);
		//char *path = "/bin/cp";
		/* als pad bestaat, fork en exec */	
		if (stat(path, &buffer) == 0)
		{
			//cp_command.args[0] = path;
			pid = fork();
				if (pid == 0)
				{
					printf("child\n");
					execve(path, cp_command.args, envp);
					//ft_execute(cp_command.args, envp);
				}
				else
				{
					printf("parent\n");
					wait(NULL);
				}
		}
		else
			printf("we zijn niet geforkt, want pad bestaat niet.\n");
		i++;
	}
	return (0);
}
