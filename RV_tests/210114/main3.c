/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:37:52 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/07 15:25:38 by rixt          ########   odam.nl         */
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
	printf("struct: %s, args[1]: %s\n", cmd->program, cmd->args[1]);
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
//	int ret;

//	while (er nog een path in paths is)
//	{
//		program = ft_strjoin(paths[i], command[0]);
//		ret = stat(const char *restrict program, struct stat *restrict buf);
//		if (stat returnt dat program bestaat)
//			return (program); //dit is je path naar het program
//	}
	//als je hier komt, bestaat het programma niet
	//return lege string en check in die functie of de string leeg is?
//	printf("command not found: %s\n", command[0]);
	


	char *path = "/bin/";
	return (ft_strjoin(path, str));
}

//nadat je stat hebt uitgevogeld, maak een functie die -1 returned als een pad/file niet bestaat en 1 als het wel bestaat. Maak een functie die paden maakt (strjoin(paths[i], command->program) en daar naar toe stuurt

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
	/*je hebt nu paths = [/path/1, path/2, etc]*/
/*append met stat command[0] aan elk path, en kijk welke bestaat*/
}

void		ft_execute(char **command, char **envp)
{
	char	*path;
	struct stat buffer;

	
	path = ft_append_path(command[0]);
	printf("we zoeken: %s\n", path);
	if (stat(path, &buffer) == 0)
		execve(path, command, envp);
	else printf("command not found: %s\n", command[0]);
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
	//hier struct maken?
	t_command cp_command;
	ft_make_struct(cp, &cp_command);
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
