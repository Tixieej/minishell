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
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

// Names of environment variables are case-sensitive and must not contain the character ‘=’. 
//System-defined environment variables are invariably uppercase.
// The values of environment variables can be anything that can be represented as a string.
//A value must not contain an embedded null character, since this is assumed to terminate the string. 
void	prompt()
{
	write(1, "\033[38;5;105mminishell: \e[0m", 27);
}

int		create_list(t_list *list, char *line, size_t *len, unsigned int start)
{
	char *temp;

	temp = ft_substr((char const *)line, start, *len);
	ft_list_push_back(&list, temp);
	start += *len;
	*len = 0;
	return (start);
}

// int		handle_quotation_marks(t_list *list, char *line, size_t len, unsigned int start, char)
// {
// 	if (line[start + len] == 39)
// 	{
// 		if (line[start + len - 1] == ' ')
// 		{
// 			start += len;
// 			len = 1;
// 		}
// 		len++;
// 		while (line[start + len] != '\0' && line[start + len] != 39)
// 			len++;
// 		if (line[start + len] != 39)
// 			printf("write function for extra input\n");
// 		len++;
// 		start = create_list(list, line, len, start);
// 		len = 0;
// 	}
// 	return (start);
// }

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
		if (line[start + len] == '>' || line[start + len] == '<' || line[start + len] == '|')
		{
			start += len;
			while (line[start + len] == '>' || line[start + len] == '<' || line[start + len] == '|')
				len++;
		}
		else
		{
			start += len;
			while (line[start + len] != '\0' && line[start + len] != ' ' && line[start + len] != 39 && line[start + len] != 34)
				len++;
		}
		if (line[start + len] == ' ' || line[start + len] == '\0')
			start = create_list(list, line, &len, start);
		if (line[start + len] == 39)
		{
			// if (line[start + len - 1] == ' ') //
			// {
			// 	start += len;
			// 	len = 1;
			// }
			// len++;
			while (line[start + len] != '\0' && line[start + len] != 39)
				len++;
			if (line[start + len] != 39)
				printf("write function for extra input\n");
			len++;
			start = create_list(list, line, &len, start);
		}
		if (line[start + len] == 34)
		{
			// if (line[start + len - 1] == ' ')
			// {
			// 	start += len;
			// 	len = 1;
			// }
			// len++;
			while (line[start + len] != '\0' && line[start + len] != 34)
				len++;
			if (line[start + len] != 34)
				printf("write function for extra input\n");
			len++;
			start = create_list(list, line, &len, start);
		}
		len++;
	}
}


// void	divide_input(t_list *list, char *line)
// {
// 	size_t			len;
// 	unsigned int	start;
// 	char			*temp;

// 	len = 0;
// 	start = 0;
// 	temp = NULL;
// 	while (line[start + len] != '\0')
// 	{
// 		while (line[start + len] == ' ')
// 			start++;
// 		if (line[start + len] == '>' || line[start + len] == '<' || line[start + len] == '|')
// 		{
// 			start += len;
// 			while (line[start + len] == '>' || line[start + len] == '<' || line[start + len] == '|')
// 				len++;
// 		}
// 		else
// 		{
// 			start += len;
// 			while (line[start + len] != '\0' && line[start + len] != ' ' && line[start + len] != 39 && line[start + len] != 34)
// 				len++;
// 		}
// 		if (line[start + len] == ' ' || line[start + len] == '\0')
// 		{
// 			start = create_list(list, line, len, start);
// 			len = 0;
// 		}
// 		if (line[start + len] == 39)
// 		{
// 			if (line[start + len - 1] == ' ')
// 			{
// 				start += len;
// 				len = 1;
// 			}
// 			len++;
// 			while (line[start + len] != '\0' && line[start + len] != 39)
// 				len++;
// 			if (line[start + len] != 39)
// 				printf("write function for extra input\n");
// 			len++;
// 			start = create_list(list, line, len, start);
// 			len = 0;
// 		}
// 		if (line[start + len] == 34)
// 		{
// 			if (line[start + len - 1] == ' ')
// 			{
// 				start += len;
// 				len = 1;
// 			}
// 			len++;
// 			while (line[start + len] != '\0' && line[start + len] != 34)
// 				len++;
// 			if (line[start + len] != 34)
// 				printf("write function for extra input\n");
// 			len++;
// 			start = create_list(list, line, len, start);
// 			len = 0;
// 		}
// 		len++;
// 	}
// }

void compare_input(t_list *list)//, char **env)
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

void	read_input(t_list *list)
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
