/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/08 11:13:43 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	write(2, "\033[38;5;105mminishell: \e[0m", 27);
}

static char	**copy_env(char **env)
{
	char	**copy;
	int		count;
	int		path;

	path = 0;
	count = 0;
	copy = NULL;
	while (env[count])
		count++;
	copy = malloc(sizeof(char *) * count + 1);
	if (!copy)
		return (NULL);
	copy[count] = NULL;
	while (count > path)
	{
		copy[path] = ft_strdup(env[path]);
		path++;
	}
	return (copy);
}

static void	start_program(char **env, char *line, int error)
{
	t_command	*command;
	t_list		*list;
	int			result;
	t_list		**begin; //

	begin = &list; //
	command = NULL;
	list = NULL;
	result = 1;
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	while (result == 1)
	{
		prompt();
		result = get_next_line(0, &line);
		if (result == -1)
			error_handler("get next line failed", list, NULL, 1);
		if (line[0] == '\0')
			continue ;
		divide_input(&list, line, 0, 0);
		// while ((*begin))// loop om te lezen wat er gebeurt, later weghalen
		// {
		// 	printf("list item: [%s]\n", (char*)((*begin)->content));
		// 	// printf("begin adress: %p\n", begin);
		// 	begin = &(*begin)->next;
		// }
		// begin = &list;
		error = parser(&list, &env, command, error);
		if (list)
		{
			ft_lstclear(&list, free); //weg?
			list = NULL; //weg?
		} 
		free(line);
		line = NULL;
	}
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	char	**cpy_env;

	(void)argv; //
	cpy_env = copy_env(env);
	if (cpy_env == NULL)
		return (-1);
	if (argc != 1)
	{
		printf("no arguments needed");
		return (0);
	}
	start_program(cpy_env, NULL, 0);
	//free env
	return (0);
}
