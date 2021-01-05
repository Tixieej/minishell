/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:37:52 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/05 18:10:10 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"

void		prompt(void)
{
	write(1, "\033[38;5;105mlrsh$ \e[0m", 22);
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

char		*ft_append_path(char *str)
{
	char *path = "/bin/";

	return (ft_strjoin(path, str));
}

void		ft_path(char **envp)
{
	char	**paths;
	char	**tmp = envp;

	while (*tmp)
	{
		if (ft_strncmp("PATH", *tmp, 4) == 0)
		{
			printf("%s\n", *tmp);
			paths = ft_split(*tmp, ':');
		}
		tmp++;
	}
}

void		ft_execute(char **command, char **envp)
{
	char	*path;

	path = ft_append_path(command[0]);
	printf("we zoeken: %s\n", path);
	execve(path, command, envp);
	printf("command not found: %s\n", command[0]);
}

int			main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		result;
	t_list	*cp;
	t_list	*echo;
	t_list	*wrong;
	char	**cp_array;
	char	**echo_array;
	char	**wrong_array;

	ft_path(envp);
	result = 1;
	(void)argv;
	(void)argc;
	cp = ft_create_elem("cp");
	ft_list_push_back(&cp, "testfile");
	ft_list_push_back(&cp, "vla");
	cp_array = ft_list_to_array(cp);
	pid = fork();
	if (pid == 0)
		ft_execute(cp_array, envp);
	else
		wait(NULL);
	echo = ft_create_elem("echo");
	ft_list_push_back(&echo, "hoi");
	ft_list_push_back(&echo, "allemaal");
	echo_array = ft_list_to_array(echo);
	pid = fork();
	if (pid == 0)
		ft_execute(echo_array, envp);
	else
		wait(NULL);
	wrong = ft_create_elem("niks");
	ft_list_push_back(&wrong, "dit betekent niks");
	wrong_array = ft_list_to_array(wrong);
	pid = fork();
	if (pid == 0)
		ft_execute(wrong_array, envp);
	else
		wait(NULL);
	return (0);
}
