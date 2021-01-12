/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/11/26 15:55:26 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

// Names of environment variables are case-sensitive and must not contain the character ‘=’. 
//System-defined environment variables are invariably uppercase.
// The values of environment variables can be anything that can be represented as a string.
//A value must not contain an embedded null character, since this is assumed to terminate the string. 
static void	prompt()
{
	write(1, "\033[38;5;105mminishell: \e[0m", 27);
}

static int		create_list(t_list *list, char *line, size_t *len, unsigned int start)
{
	char *temp;

	temp = ft_substr((char const *)line, start, *len);
	ft_list_push_back(&list, temp);
	start += *len;
	*len = -1;
	return (start);
}

static int		handle_quotation_marks(t_list *list, char *line, size_t *len, unsigned int start)
{
	if (line[start + *len] == '\'')
	{
		(*len)++;
		while (!ft_strchr("\'\0", line[start + *len]))
			(*len)++;
		if (line[start + *len] != '\'')
			printf("write function for extra input\n");
		(*len)++;
		start = create_list(list, line, len, start);
	}
	else if (line[start + *len] == '\"')
	{
		(*len)++;
		while (!ft_strchr("\"\0", line[start + *len]))
			(*len)++;
		if (line[start + *len] != '\"')
			printf("write function for extra input\n");
		(*len)++;
		start = create_list(list, line, len, start);
	}
	return (start);
}

void	divide_input(t_list *list, char *line)
{
	size_t			len;
	unsigned int	start;
	char			*temp;

	len = 0;
	start = 0;
	temp = NULL;
	while (line[start + len] != '\0')
	{
		while (line[start + len] == ' ')
			start++;
		if (ft_strchr("|<>", line[start + len]))
		{
			start += len;
			while (ft_strchr("|<>", line[start + len]))
				len++;
		}
		else if (!ft_strchr("\'\"", line[start + len]))
		{
			start += len;
			while (!ft_strchr(" \'\"\0", line[start + len]))
				len++;
		}
		if (line[start + len] == ' ' || line[start + len] == '\0')
			start = create_list(list, line, &len, start);
		if (ft_strchr("\'\"", line[start + len]))
			start = handle_quotation_marks(list, line, &len, start);
		len++;
	}
}

static void compare_input(t_list *list)//, char **env)
{
	t_list	*begin;

	begin = list;
	while (begin)
	{
		if (ft_strncmp((const char *)begin->content , "cat", 3) == 0)
			printf("cat type\n");
		if (ft_strncmp((const char *)begin->content , "cp", 2) == 0)
			printf("cp type\n");
		if (ft_strncmp((const char *)begin->content , "echo", 4) == 0)
			printf("echo type\n");
		begin = begin->next;
	}
	begin = list;
}

static void	read_input(t_list *list)
{
	int 	result;
	char	*line;
	t_list	*begin;

	begin = list;
	result = 1;
	line = NULL;
	while (result == 1)
	{
		prompt();
		result = get_next_line(0, &line);
		divide_input(list, line);
		begin = list->next;
		compare_input(list); //check welke type het is
		while (begin) // loop om te lezen wat er gebeurd
		{
			printf("list item: [%s]\n", (char*)(begin->content));
			// printf("begin adress: %p\n", begin);
			begin = begin->next;
		}
		ft_lstclear(&list, free);
		list = ft_create_elem(ft_strdup("start"));
		begin = list;
		free(line);
		line = NULL;
	}
}

int		main(int argc, char **argv)//, char **env)
{
	t_list	*list;

	list = ft_create_elem(ft_strdup("start"));
	(void)argv;
	if (argc != 1)
	{
		printf("no arguments needed"); //
		return (0);
	}
	read_input(list);
	return (0);
}
