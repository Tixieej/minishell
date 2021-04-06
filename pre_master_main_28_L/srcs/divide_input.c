/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/02 14:23:30 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trim_quotation_marks(char *temp, char *type, int len, int i)
{
	char	*temp_tr;

	temp_tr = NULL;
	len = ft_strlen(temp);
	while (temp[i] != '\0')
	{
		if (temp[i] == '\"' || temp[i] == '\'')
		{
			if (i > 1)
				type = ft_substr(temp, 0, i);
			temp_tr = ft_substr(temp, i + 1, len - 2);
			free(temp);
			if (type)
				temp = ft_strjoin(type, temp_tr);
			else
				temp = ft_strdup(temp_tr);
			free(temp_tr);
			free(type);
			return (temp);
		}
		i++;
	}
	return (temp);
}

static int	create_list_item(t_list **list, char *line,
								size_t *len, unsigned int start)
{
	char	*temp;

	temp = ft_substr((char const *)line, start, *len);
	// if (temp[0] == '\'' && temp[1] == '$')
	temp = trim_quotation_marks(temp, NULL, 0, 0);
	ft_list_push_back(list, temp);
	// if (line[start + *len] == ';')
	// 	ft_list_push_back(list, ft_strdup(";"));
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
		while (line[start + *len] != '\'' && line[start + *len] != '\0')
			(*len)++;
		if (line[start + *len] != '\'')
			error_handler("missing quotation marks\n", *list, NULL, 1);
		(*len)++;
		start = create_list_item(list, line, len, start);
	}
	else if (line[start + *len] == '\"')
	{
		start++;
		while (line[start + *len] != '\"' && line[start + *len] != '\0')
			(*len)++;
		if (line[start + *len] != '\"')
			error_handler("missing quotation marks\n", *list, NULL, 1);
		(*len)++;
		start = create_list_item(list, line, len, start);
	}
	start += *len;
	*len = 0;
	return (start);
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
			error_handler("error near unexpected token`>'\n", *list, NULL, 258);
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
