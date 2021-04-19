/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/19 10:42:08 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*check_exp_within_dq(t_base *base, char *str, char *exp, int count)
// {
// 	size_t	start;
// 	size_t	len;
// 	char	*str_left;
// 	char	*temp;
// 	int		check;

// 	check = 0;
// 	start = 1;
// 	len = 0;
// 	str_left = NULL;
// 	temp = NULL;
// 	while (str[start + len] != '\0')
// 	{
// 		if (str[start + len] == '$')
// 		{
// 			start += len + 1;
// 			len = 0;
// 			while (str[start + len] != '\0' && str[start + len] != '$' && str[start + len] != '\"')
// 				len++;
// 			while (base->env[count])
// 			{
// 				if (ft_strncmp(base->env[count], &str[start], len) == 0)
// 				{
// 					check = 1;
// 					if (str[start + len] != '\0' && str[start + len] != '\"')
// 						str_left = ft_strdup(&str[start + len]);
// 					exp = ft_strdup(&base->env[count][len + 1]);
// 					temp = ft_substr(str, 1, start - 2);
// 					free(str); //
// 					str = ft_strjoin(temp, exp);
// 					free(temp); //
// 					if (str_left)
// 					{
// 						temp = ft_strjoin(str, str_left);
// 						start = ft_strlen(str) - 1;
// 						free(str);
// 						str = ft_strdup(temp);
// 						free(temp);
// 					}
// 					else
// 						start = start + len + ft_strlen(exp);
// 					// if (exp)
// 					// 	free(exp); //
// 					len = 0;
// 					if (str_left)
// 						free(str_left); //
// 					count = 0;
// 					break;
// 				}
// 				count++;
// 			}
// 		}
// 		len++;
// 	}
// 	if (check == 0)
// 	{
// 		free(str);
// 		str = ft_strdup("");
// 	}
// 	return (str);
// }

static char	*enter_expansion(char *str, int *start, int *len, char *env)
{
	char	*str_end;
	char	*str_start;
	char	*exp;
	char	*temp;

	temp = NULL;
	str_end = NULL;
	exp = ft_strdup(&env[*len + 1]);
	printf("exp %s\n", exp);
	if (str[*start + *len] == '$')
		str_end = ft_strdup(&str[*start + *len]);
	str_start = ft_substr(str, 1, *start - 2);
	printf("start %s\n", str_start);
	temp = ft_strjoin(str_start, exp);
	*len += ft_strlen(exp);
	free(str);
	if (str_end)
	{
		str = ft_strjoin(temp, str_end);
		*len += ft_strlen(str_end);
	}
	else	
		str = ft_strdup(temp);
	free(temp);
	free(str_end);
	free(str_start);
	return (str);
}

static char	*check_exp_within_dq(t_base *base, char *str, int start, int count)
{
	int	len;
	int	check;

	len = 0;
	check = 0;
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
					check = 1;
					str = enter_expansion(str, &start, &len, base->env[count]);
					count = 0;
					printf("str %s\n", str);
					printf("len: %d\n", len);
					printf("start: %d\n", start);
					printf("char: %d\n", str[start + len]);
					break;
				}
				count++;
			}
		}
		len++;
	}
	return(str);
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
			temp_tr = check_exp_within_dq(base, temp_tr, 0, 0);
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
