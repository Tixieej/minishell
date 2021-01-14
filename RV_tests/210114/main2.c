/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:37:52 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/05 14:33:58 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

t_list		*ft_create_elem(void *data);
void		ft_list_push_back(t_list **begin_list, void *data);
typedef int	t_size_t;
char		**ft_split(char const *s, char c);

void	prompt()
{
	write(1, "\033[38;5;105mlrsh$ \e[0m", 22);
}

int			ft_strncmp(char *s1, char *s2, t_size_t n)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s2[i] != '\0')
	{
		if (i >= n)
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (s1[i] - s2[i]);
}

char	**ft_list_to_array(t_list *list)
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

char	*ft_append_path(char *str)//todo
{
	char *path = "/bin/";
	return(ft_strjoin(path, str));
}

void	ft_execute(char **command, char **envp)
{
	char	*path;

	path = ft_append_path(command[0]);
	printf("we zoeken: %s\n", path);
	execve(path, command, envp);
	printf("command not found: %s\n", command[0]);
}

/* onderstaande functie wordt vervangen door ft_execute */
void	ft_copy(char **command, char **envp)
{
	(void)(command);
	char *args[] = {"/bin/cp", "testfile", "vla", NULL};

	execve(args[0], args, envp);
}

int     main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	//char	*line;
	int		result;
	//t_list *list;
	//int j = 0;
	//char **command;

	result = 1;
	//line = NULL;
	(void)argv;
	(void)argc;
/*
	if (argc != 1)
	{
		printf("no arguments needed"); //
		return (0);
	}
*/

/*		dit gaat tijdelijk? in de comments */
/*	while (result == 1)
	{
		prompt();
		result = get_next_line(0, &line);
		

//		Hier komt code die de ingelezen line van gnl split op spaties en van elk 'woord' een element in een linked list maakt //

		command = ft_split(line, ' ');//nu is het een array, dat wil je niet
		//herschrijf ft_split zodat linked list...
		ft_list_push_back(&list, line);//elementen zijn woorden in line, niet line zelf
		//free(line);		
//		Einde stuk dat nog komt	//

		if (ft_strncmp(line, "cp ", 2) == 0)
		{
			printf("yay copy is aangeroepen, wat nu?\n");
			pid = fork();
			if (pid == 0)
				ft_copy(command, envp);
			else
			{
				wait(NULL);
				printf("parent\n");
			}
		}
		else if (ft_strncmp(line, "echo ", 4) == 0)
		{
			pid = fork();
			if (pid == 0)
				ft_echo(command, envp);
			else
				wait(NULL);
		}
	}
//		Einde tijdelijke? comment */

	t_list *cp;
	cp = ft_create_elem("cp");
	ft_list_push_back(&cp, "testfile");
	ft_list_push_back(&cp, "vla");
	char **cp_array = ft_list_to_array(cp);
	pid = fork();
	if (pid == 0)
		ft_execute(cp_array, envp);
	else
		wait(NULL);
	
	t_list *echo;
	echo = ft_create_elem("echo");
	ft_list_push_back(&echo, "hoi");
	ft_list_push_back(&echo, "allemaal");
	char **echo_array = ft_list_to_array(echo);
	pid = fork();
	if (pid == 0)
		ft_execute(echo_array, envp);
	else
		wait(NULL);

	t_list *wrong;
	wrong = ft_create_elem("niks");
	ft_list_push_back(&wrong, "dit betekent niks");
	char **wrong_array = ft_list_to_array(wrong);
	pid = fork();
	if (pid == 0)
		ft_execute(wrong_array, envp);
	else
		wait(NULL);

/*
	while (list)
	{
		printf("element %i in list: [%s]\n", j, (char*)list->data);
		printf("adres naar volgende element: %p\n", list->next);
		list = list->next;
		j++;
	}
*/
	return (0);
}
