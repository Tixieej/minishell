/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/12 17:14:11 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	write(2, "\033[38;5;105mminishell: \e[0m", 27);
}

int	copy_env(t_base *base, char **env)
{
	// char	**copy;
	int		count;
	int		path;

	path = 0;
	count = 0;
	// copy = NULL;
	while (env[count])
		count++;
	base->env = malloc(sizeof(char *) * count + 1);
	if (!base->env)
		return (0);
	base->env[count] = NULL;
	while (count > path)
	{
		base->env[path] = ft_strdup(env[path]);
		path++;
	}
	return (1);
}

static void	start_program(t_base *base, char *line, int error)
{
	t_command	*command;
	// t_list		*list;
	int			result;
	t_list		**begin; //

	begin = &base->list; //
	command = NULL;
	base->list = NULL;
	result = 1;
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	while (result == 1)
	{
		prompt();
		result = get_next_line(0, &line);
		if (result == -1)
			error_handler("get next line failed", base->list, NULL, 1);
		if (line[0] == '\0')
			continue ;
		divide_input(base, line, 0, 0);
		// while (*begin) //loop om te lezen wat er gebeurt, later weghalen
		// {
		// 	printf("\tbase->list item: [%s]\n", (char*)((*begin)->content));
		// 	// printf("begin adress: %p\n", begin);
		// 	begin = &(*begin)->next;
		// }
		// begin = &base->list;
		error = parser(&base->list, &base->env, command, error);
		if (base->list)
		{
			ft_lstclear(&base->list, free); //weg?
			base->list = NULL; //weg?
		}
		free(line);
		line = NULL;
	}
	exit(0);
}

static t_base *ft_create_base_struct(char **env)
{
	t_base	*base;

	base = malloc(sizeof(t_base));
	if (!base)
		return (NULL);
	if (base)
	{
		if (copy_env(base, env) == 0)
			return (NULL);
		base->list = NULL;
	}
	return (base);
}

int	main(int argc, char **argv, char **env)
{
	t_base	*base;

	(void)argv; //
	base = ft_create_base_struct(env);
	if (!base)
		return (-1);
	if (argc != 1)
	{
		printf("no arguments needed");
		return (0);
	}
	start_program(base, NULL, 0);
	free(base); //genoeg?
	//free env
	return (0);
}
