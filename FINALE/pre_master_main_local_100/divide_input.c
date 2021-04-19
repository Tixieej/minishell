/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/16 11:41:52 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_exp_within_dq(t_base *base, char *str, char *exp, int count)
{
	size_t	start;
	size_t	len;
	char	*str_left;
	char	*temp;

	start = 1;
	len = 0;
	str_left = NULL;
	temp = NULL;
	while (str[start + len] != '\0')
	{
		if (str[start + len] == '$')
		{
			start += len + 1;
			len = 0;
			while (str[start + len] != '\0' && str[start + len] != '$' && str[start + len] != '\"')
				len++;
			while (base->env[count])
			{
				if (ft_strncmp(base->env[count], &str[start], len) == 0)
				{
					if (str[start + len] != '\0' && str[start + len] != '\"')
						str_left = ft_strdup(&str[start + len]);
					printf("str_left: %s\n", str_left);
					exp = ft_strdup(&base->env[count][len + 1]);
					temp = ft_substr(str, 1, start - 2);
					printf("temp: %s\n", temp);
					free(str);
					printf("exp: %s\n", exp);
					str = ft_strjoin(temp, exp);
					printf("str 1: %s\n", str);
					free(temp);
					if (str_left)
					{
						temp = ft_strjoin(str, str_left);
						free(temp);
						free(str);
						str = ft_strdup(temp);
					}
					start = start + len + ft_strlen(exp);
					len = 0;
					free(exp);
					if (str_left)
						free(str_left);
					count = 0;
					break;
				}
				count++;
			}
			
		}
		len++;
	}
	printf("result str: %s\n", str);
	// if (len > 0)
	// 	strjoin
	return (str);
}
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
			// printf("temp_tr: %s\n", temp_tr);
			temp_tr = check_exp_within_dq(base, temp_tr, NULL, 0);
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
	if (temp[0] == '\'' && temp[1] == '$')
		ft_list_push_back(&base->list, temp);
	else
	{
		temp = trim_quotation_marks(base, temp, NULL, 0);
		ft_list_push_back(&base->list, temp);
	}
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

static void	prep_redirection(char *line, unsigned int *start, size_t *len)
{
	if (line[*start + *len] == '>' && line[*start + *len + 1] == '>')
	{
		(*start)++;
		*len = 2;
	}
	if (line[*start + *len] == '>' || line[*start + *len] == '<')
		(*len)++;
}

void	divide_input(t_base *base, char *line,
							size_t len, unsigned int start)
{
	while (line[start + len] != '\0')
	{
		while (line[start + len] == ' ')
			start++;
		if (!ft_strchr("';'' ''<''>'\'\"'\0'", line[start + len]))
		{
			start += len;
			while (!ft_strchr("';'' ''<''>' \'\"'\0'", line[start + len]))
				len++;
		}
		if (!ft_strncmp(&line[start + len], ">>>", 3))
			error_handler("error near unexpected token`>'\n", base->list, NULL, 258);
		if (ft_strchr("\'\"", line[start + len]) && line[start + len] != '\0')
			start = handle_quotation_marks(base, line, &len, start);
		if (ft_strchr("'<''>'';'' ''\0'", line[start + len]))
		{
			if (line[start + len] == '>' || line[start + len] == '<')
				prep_redirection(line, &start, &len);
			if (len != 0)
				start = create_list_item(base, line, &len, start);
		}
		if (line[start + len] == ';')
			ft_list_push_back(&base->list, ft_strdup(";"));
		start++;
	}
}
