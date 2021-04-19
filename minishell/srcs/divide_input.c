/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/19 16:47:32 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trim_quotation_marks(t_base *base, char *temp, char *type, int len)
{
	char	*temp_tr;
	int		start;

	temp_tr = NULL;
	start = 0;
	while (!ft_strchr("';'' ''<''>'\'\"'\0'", temp[len]))
			(len)++;
	while (temp[start] != '\0')
	{
		if (temp[start] == '\"' || temp[start] == '\'')
		{
			if (start > 1)
			{
				type = ft_substr(temp, 0, start);
				len -= start;
			}
			temp_tr = ft_substr(temp, start, len - 2);
			temp_tr = check_exp_within_dq(base->env, temp_tr, 0, 0);
			free(temp);
			if (type)
				temp = ft_strjoin(type, temp_tr);
			else
				temp = ft_strdup(temp_tr);
			free(temp_tr);
			free(type);
		}
		start++;
	}
	return (temp);
}

static int	create_list_item(t_base *base, char *line,
								size_t *len, unsigned int start)
{
	char	*temp;

	temp = NULL;
	temp = ft_substr((char const *)line, start, *len);
	temp = trim_quotation_marks(base, temp, NULL, 0);
		ft_list_push_back(&base->list, temp);
	if (line[start + *len] != '\0')
		start += *len;
	else
		start += *len - 1;
	*len = 0;
	return (start);
}

static int	handle_quotation_marks(t_base *base, char *line,
									size_t *len, unsigned int start)
{
	if (line[start + *len] == '\'')
	{
		(*len)++;
		while (line[start + *len] != '\'' && line[start + *len] != '\0')
			(*len)++;
		if (line[start + *len] != '\'')
			error_handler("missing quotation marks\n", base->list, NULL, 2);
		(*len)++;
		while (!ft_strchr("';'' ''<''>'\'\"'\0'", line[start + *len]))
			(*len)++;
		start = create_list_item(base, line, len, start);
	}
	else if (line[start + *len] == '\"')
	{
		(*len)++;
		while (line[start + *len] != '\"' && line[start + *len] != '\0')
			(*len)++;
		if (line[start + *len] != '\"')
			error_handler("missing quotation marks\n", base->list, NULL, 2);
		(*len)++;
		while (!ft_strchr("';'' ''<''>'\'\"'\0'", line[start + *len]))
			(*len)++;
		start = create_list_item(base, line, len, start);
	}
	start += *len;
	*len = 0;
	return (start);
}

static void	handle_redirection(t_base *base, char *line, size_t *len, unsigned int *start)
{
	if (line[*start + *len] == '>' && line[*start + *len + 1] == '>')
		{
			ft_list_push_back(&base->list, ft_strdup(">>"));
			*start += 1;
		}
	else if (line[*start + *len] == '>' || line[*start + *len] == '<')
			ft_list_push_back(&base->list, ft_strdup(">"));
}

void    divide_input(t_base *base, char *line,
                            size_t len, unsigned int start)
{
	while (line[start + len] != '\0')
	{
		while (line[start + len] == ' ')
			start++;
		if (!ft_strchr("'|'';'' ''<''>'\'\"'\0'", line[start + len]))
		{
			start += len;
			while (!ft_strchr("'|'';'' ''<''>' \'\"'\0'", line[start + len]))
				len++;
		}
		if (!ft_strncmp(&line[start + len], ">>>", 3))
			error_handler("error near unexpected token`>'\n", base->list, NULL, 258);
		if (ft_strchr("\'\"", line[start + len]) && line[start + len] != '\0')
			start = handle_quotation_marks(base, line, &len, start);
		if (ft_strchr("'|''<''>'';'' ''\0'", line[start + len]))
		{
			if (len != 0)
				start = create_list_item(base, line, &len, start);
		}
		if (line[start + len] == '>')
			handle_redirection(base, line, &len, &start);
		if (line[start + len] == ';')
			ft_list_push_back(&base->list, ft_strdup(";"));
		if (line[start + len] == '|')
			ft_list_push_back(&base->list, ft_strdup("|"));
		start++;
	}
}
