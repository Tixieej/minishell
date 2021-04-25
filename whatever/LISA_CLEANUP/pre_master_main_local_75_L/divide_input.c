/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/12 17:13:26 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_exp_within_dq(t_base *base, char *str, char *exp, int count)
{
	size_t	start;
	size_t	len;

	// len = ft_strlen(str);
	(void)base;
	start = 1;
	len = 0;
	count = 0;
	exp = NULL;
	// while (str[start + len] != '\0')
	// {
	// 	if (str[start + len] == '$')
	// 	{
	// 		while (str[start + len] != '\0' && str[start + len] != '$')
	// 			len++;
	// 		while (base->env[count])
	// 		{
	// 			printf("base: %s\n", base->env[count]);
	// 			printf("str: %s\n", &str[len + 2]);
	// 			printf("len %zu\n", ft_strlen(&str[len + 3]);
	// 			if (ft_strncmp(base->env[count], &str[len + 2], ft_strlen(&str[len + 2]) - 1) == 1)
	// 			{
	// 				printf("ja");
	// 				// check = 1;
	// 				// exp = ft_strdup(base->env[len]);
	// 				// free(str);
	// 				// if (temp_len < ft_strlen(str))
	// 				// 	str = ft_strjoin(exp, str);
	// 				// else
	// 				// 	str = ft_strdup(exp);
	// 			}
	// 			count++;
	// 		}
	// 		count = 0;
	// 	}
	// 	len++;
	// }
	// printf("exp: %s\n", exp);
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
