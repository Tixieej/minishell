/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide_input_backup.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/29 13:18:48 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// dit was divide_input die jij hebt aangepast zodat echo hallo;echo doei werkt, maar > slaat ie over
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
	{
		ft_list_push_back(list, ft_strdup(";"));
		start++;
	}
	start += *len;
	*len = 0;
	return (start);
}

static int	handle_quotation_marks(t_list **list, char *line,
									size_t *len, unsigned int start)
{
	if (line[start + *len] == '\'')
	{
		start++;
		while (!ft_strchr("\'\0", line[start + *len])) // "\''\0'"
			(*len)++;
		if (line[start + *len] != '\'')
			error_handler("missing quotation marks\n", *list, NULL);
		start = create_list_item(list, line, len, start); //+1
		(*len)++;
	}
	else if (line[start + *len] == '\"')
	{
		start++;
		while (!ft_strchr("\"\0", line[start + *len])) // "\"'\0'" // *len + 1
			(*len)++;
		if (line[start + *len] != '\"') // *len + 1
			error_handler("missing quotation marks\n", *list, NULL);// hieronder start++
		start = create_list_item(list, line, len, start);
		(*len)++;// deze niet
	}
	return (start);
}

void	divide_input(t_list **list, char *line,
							size_t len, unsigned int start)
{
	while (line[start + len] != '\0')
	{
		while (line[start + len] == ' ' && line[start + len] != '\0')
			start++;
		if (!ft_strchr("'<''>'\'\"'\0'';'", line[start + len]))
		{
			start += len;
			while (!ft_strchr("';''<''>' \'\"'\0'", line[start + len]))
				len++;
		}
		if (!ft_strncmp(&line[start + len], ">>>", 3))
			error_handler("error near unexpected token`>'\n", *list, NULL);
		if (ft_strchr("';'' '<''>''\0'", line[start + len]))
		{
			if (len < 1 && line[start + len + 1] == '>')
				len = 2;
			if (line[start + len] == '>' || line[start + len] == '<')
				len = 1;
			if (len != 0)
				start = create_list_item(list, line, &len, start);
		}
		write(2, "\t\thierna\n", 9);
		if (ft_strchr("\'\"", line[start + len]))
			start = handle_quotation_marks(list, line, &len, start);
		len++;
	}
}
