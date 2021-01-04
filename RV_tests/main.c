/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/20 12:37:52 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/04 14:46:17 by rixt          ########   odam.nl         */
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
		{
			return (s1[i] - s2[i]);
		}
		else
		{
			i++;
		}
	}
	return (s1[i] - s2[i]);
}


void	ft_copy(char **command, char **envp)
{
	printf("kijk nu of het nieuwe bestand er staat\n");
	(void)(command);
	char *args[] = {"/bin/cp", "testfile", "vla", NULL};

	execve(args[0], args, envp);
}

void	ft_echo(char **command, char **envp)
{
	(void)(command);
	char *args[] = {"/bin/echo", "success", NULL};

	execve(args[0], args, envp);
}

int     main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	char	*line;
	int		result;
	t_list *list;
	int j = 0;
	char **command;

	result = 1;
	//line = NULL;
	(void)argv;
	if (argc != 1)
	{
		printf("no arguments needed"); //
		return (0);
	}
	while (result == 1)
	{
		prompt();
		result = get_next_line(0, &line);
		

/*		Hier komt code die de ingelezen line van gnl split op spaties en van elk 'woord' een element in een linked list maakt
		command = ft_split(line, ' ');//nu is het een array, dat wil je niet
		//herschrijf ft_split zodat linked list...
		ft_list_push_back(&list, line);//elementen zijn woorden in line, niet line zelf
		//free(line);		
*/

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

	while (list)
	{
		printf("element %i in list: [%s]\n", j, (char*)list->data);
		printf("adres naar volgende element: %p\n", list->next);
		list = list->next;
		j++;
	}
	return (0);
}
