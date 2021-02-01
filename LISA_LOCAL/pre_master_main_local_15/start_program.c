/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_program.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/28 17:59:16 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		prompt(void)
{
	write(1, "\033[38;5;105mminishell: \e[0m", 27);
}

static int		create_list_item(t_list **list, char *line,
								size_t *len, unsigned int start)
{
	char *temp;

	temp = ft_substr((char const *)line, start, *len);
	ft_list_push_back(list, temp);
	start += *len;
	*len = -1;
	return (start);
}

static int		handle_quotation_marks(t_list **list, char *line,
									size_t *len, unsigned int start)
{
	if (line[start + *len] == '\'')
	{
		(*len)++;
		while (!ft_strchr("\'\0", line[start + *len]))
			(*len)++;
		if (line[start + *len] != '\'')
			error_handler("missing quotation marks\n", list, NULL);
		(*len)++;
		start = create_list_item(list, line, len, start);
	}
	else if (line[start + *len] == '\"')
	{
		(*len)++;
		while (!ft_strchr("\"\0", line[start + *len]))
			(*len)++;
		if (line[start + *len] != '\"')
			error_handler("missing quotation marks\n", list, NULL);
		(*len)++;
		start = create_list_item(list, line, len, start);
	}
	return (start);
}

static void		divide_input(t_list **list, char *line,
							size_t len, unsigned int start)
{
	while (line[start + len] != '\0')
	{
		while (line[start + len] == ' ')
			start++;
		if (!ft_strchr("'<''>'\'\"", line[start + len]) && line[start + len] != '\0')
		{
			start += len;
			while (!ft_strchr("'<''>' \'\"\0", line[start + len]) && line[start + len] != '\0')
				len++;
		}
		if (line[start + len] == '>' && line[start + len + 1] == '>' && line[start + len + 2] == '>')
			error_handler("syntax error near unexpected token `>'\n", list, NULL);
		if (line[start + len] == ' ' || line[start + len] == '\0' || line[start + len] == '>' || line[start + len] == '<')
		{
			if (len < 1 && line[start + len + 1] == '>')
				len = 2;
			if (len < 1)
				len = 1;
			start = create_list_item(list, line, &len, start);
		}
		if (ft_strchr("\'\"", line[start + len]))
			start = handle_quotation_marks(list, line, &len, start);
		len++;
	}
}

void			start_program(t_list *list, char **env)
{
	int			result;
	char		*line;
	t_list		**begin;
	t_command	*command;

	command = NULL;
	begin = &list;
	result = 1;
	line = NULL;
	while (result == 1)
	{
		prompt();
		result = get_next_line(0, &line);
		divide_input(&list, line, 0, 0);
		parser(&list, env, command);
		while ((*begin))// loop om te lezen wat er gebeurd later weghalen
		{
			printf("list item: [%s]\n", (char*)((*begin)->content));
			// printf("begin adress: %p\n", begin);
			begin = &(*begin)->next;
		}
		ft_lstclear(&list, free);
		begin = &list;
		free(line);
		line = NULL;
	}
	ft_lstclear(&list, free);
	exit(0);
}
