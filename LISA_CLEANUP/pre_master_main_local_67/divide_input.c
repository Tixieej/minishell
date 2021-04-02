/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/30 11:31:49 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	write(2, "\033[38;5;105mminishell: \e[0m", 27);
}

static int	create_list_item(t_list **list, char *line,
								size_t *len, unsigned int start)
{
	char	*temp;

	temp = ft_substr((char const *)line, start, *len);
	ft_list_push_back(list, temp);
	if (line[start + *len] == ';')
		ft_list_push_back(list, ft_strdup(";"));
	if (line[start + *len] != '\0')
		start += *len;
	else
		start += *len - 1;
	*len = 0;
	return (start);
}

static int	handle_quotation_marks(t_list **list, char *line,
									size_t *len, unsigned int start)
{
	if (line[start + *len] == '\'')
	{
		start++;
		while (line[start + *len + 1] != '\'' && line[start + *len + 1] != '\0')
			(*len)++;
		if (line[start + *len + 1] != '\'')
			error_handler("missing quotation marks\n", *list, NULL);
		start++;
		start = create_list_item(list, line, len, start);
	}
	else if (line[start + *len] == '\"')
	{
		start++;
		while (line[start + *len + 1] != '\"' && line[start + *len + 1] != '\0')
			(*len)++;
		if (line[start + *len + 1] != '\"')
			error_handler("missing quotation marks\n", *list, NULL);
		start++;
		start = create_list_item(list, line, len, start);
	}
	return (start + *len);
}

static void	prep_redirection(char *line, unsigned int *start, size_t *len)
{
	if (line[*start + *len] == '>' && line[*start + *len + 1] == '>')
	{
		(*start)++;
		*len = 2;
	}
	if (line[*start + *len] == '>' || line[*start + *len] == '<')
		(*start)++;
}

void	divide_input(t_list **list, char *line,
							size_t len, unsigned int start)
{
	while (line[start + len] != '\0')
	{
		while (line[start + len] == ' ')
			start++;
		if (!ft_strchr("' ''<''>'\'\"'\0'';'", line[start + len]))
		{
			start += len;
			while (!ft_strchr("' '';''<''>' \'\"'\0'", line[start + len]))
				len++;
		}
		if (!ft_strncmp(&line[start + len], ">>>", 3))
			error_handler("error near unexpected token`>'\n", *list, NULL);
		if (ft_strchr("\'\"", line[start + len]) && line[start + len] != '\0')
			start = handle_quotation_marks(list, line, &len, start);
		if (ft_strchr("';'' ''<''>''\0'", line[start + len]) && len > 0)
		{
			if (line[start + len] == '>' || line[start + len] == '<')
				prep_redirection(line, &start, &len);
			if (len != 0)
				start = create_list_item(list, line, &len, start);
		}
		len++;
	}
}