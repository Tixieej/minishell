/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/23 13:00:00 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_list_item(t_base *base, char *line,
	size_t *len, int start)
{
	char	*temp;
	int		check;

	temp = NULL;
	check = 0;
	temp = ft_substr((char const *)line, start, *len);
	temp = check_expansion(base, temp, 0, 0);
	if (temp[0] != '\0')
		ft_list_push_back(&base->list, temp);
	else
		free(temp);
	if (line[start + *len] != '\0')
		start += *len;
	else
		start += *len - 1;
	*len = 0;
	return (start);
}

static void	check_missing_q_two(char *temp, unsigned int *start,
	size_t *len, char type)
{
	(*len)++;
	while (temp[*start + *len] != type && temp[*start + *len] != '\0')
		(*len)++;
	if (temp[*start + *len] != type)
		error_handler("missing quotation marks\n", NULL, NULL, 2);
}

static void	check_missing_q(char *temp, unsigned int *start, size_t *len)
{
	while (temp[*start + *len] != '\0')
	{
		if (temp[*start + *len] == ' ')
			break ;
		if (temp[*start + *len] == '\'')
		{
			check_missing_q_two(temp, start, len, '\'');
			if (temp[*start + *len] == ' ' || temp[*start + *len] == '\0')
				break ;
		}
		else if (temp[*start + *len] == '\"')
		{
			check_missing_q_two(temp, start, len, '\"');
			if (temp[*start + *len] == ' ' || temp[*start + *len] == '\0')
				break ;
		}
		(*len)++;
	}
}

static void	handle_redirection(t_base *base, char *line,
	size_t *len, unsigned int *start)
{
	if (line[*start + *len] == '<')
		ft_list_push_back(&base->list, ft_strdup("<"));
	if (line[*start + *len] == '>' && line[*start + *len + 1] == '>')
	{
		ft_list_push_back(&base->list, ft_strdup(">>"));
		*start += 1;
	}
	else if (line[*start + *len] == '>')
		ft_list_push_back(&base->list, ft_strdup(">"));
}

void	divide_input(t_base *base, char *line,
	size_t len, unsigned int start)
{
	while (line[start + len] != '\0')
	{
		while (line[start + len] == ' ')
			start++;
		if (!ft_strchr("'|'';'' ''<''>''\'''\"''\0'", line[start + len]))
		{
			while (!ft_strchr("'|'';'' ''\'''\"''<''>''\0'", line[start + len]))
				len++;
		}
		if (!ft_strncmp(&line[start + len], ">>>", 3))
			error_handler("error near unexpected token`>'\n",
				base->list, NULL, 258);
		if (line[start + len] == '\'' || line[start + len] == '\"')
			check_missing_q(line, &start, &len);
		if (ft_strchr("'|''<''>'';'' ''\0'", line[start + len]))
			if (len != 0)
				start = create_list_item(base, line, &len, start);
		if (line[start + len] == '>' || line[start + len] == '<')
			handle_redirection(base, line, &len, &start);
		if (line[start + len] == ';' || line[start + len] == '|')
			ft_list_push_back(&base->list, ft_substr(line, start + len, 1));
		start++;
	}
}
