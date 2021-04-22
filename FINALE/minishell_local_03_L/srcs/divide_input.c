/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/22 15:28:58 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*enter_expansion(char *str, unsigned int *start, size_t *len, char *env)
{
	char	*str_start;
	char	*str_end;
	char	*str_temp;

	str_start = ft_strdup("");
	str_temp = NULL;
	str_end = ft_strdup("");
	if (*start > 1)
		str_start = ft_substr(str, 0, (size_t)*start - 1);
	if (*start + *len < ft_strlen(str))
		str_end = ft_strdup(&str[*start + *len]);
	str_temp = ft_strjoin(str_start, env);
	free(str);
	str = ft_strjoin(str_temp, str_end);
	*start = ft_strlen(str_start) + ft_strlen(env) - 1;
	*len = 0;
	free(str_start);
	free(str_end);
	free(str_temp);
	return (str);
}

static char	*expansion(t_base *base, char *temp, unsigned int *start, size_t *len)
{
	int		count;
	char	*expansion;

	count = 0;
	expansion = ft_strdup("");
	if (*len > 0)
		*start += *len;
	if (*len > 0)
		*len = 0;
	(*start)++;
	while (!ft_strchr("'$''\'''\"''\0'", temp[*start + *len]))
		(*len)++;
	while (base->env[count])
	{
		if (ft_strncmp(base->env[count], &temp[*start], *len) == 0
				&& base->env[count][*len] == '=')
		{
			free(expansion);
			expansion = ft_strdup(&base->env[count][*len + 1]);
			count = 0;
			break ;
		}
		count++;
	}
	temp = enter_expansion(temp, start, len, expansion);
	return (temp);
}

static void	free_all(char *str_start, char *str_end, char *str_temp, char *loose)
{
	free(str_start);
	free(str_end);
	free(str_temp);
	free(loose);

}

static char	*trim_quotation_marks(char type, char *str, unsigned int *start, size_t *len)
{
	char	*str_start;
	char	*str_end;
	char	*str_temp;
	char	*loose;

	loose = NULL;
	str_start = ft_strdup("");
	str_temp = NULL;
	str_end = ft_strdup("");
	while (str[*start + *len] != type && str[*start + *len] != '\0')
		(*len)++;
	loose = ft_substr(str, *start + 1, *len - 1);
	if (*start > 1)
		str_start = ft_substr(str, 0, (size_t)*start);
	if (*start + *len < ft_strlen(str) - 1)
		str_end = ft_strdup(&str[*start + *len]);
	str_temp = ft_strjoin(str_start, loose);
	free(str);
	str = ft_strjoin(str_temp, str_end);
	if (type == '\'')
		*start = ft_strlen(str_start) + ft_strlen(loose);
	if (type == '\"')
		*start = ft_strlen(str_start);
	free_all(str_start, str_end, str_temp, loose);
	return (str);
}

static char	*check_expansion(t_base *base, char *temp, size_t len, unsigned int start)
{
	while (temp[start + len] != '\0')
	{
		if (temp[start + len] == '\"')
		{
			len++;
			temp = trim_quotation_marks('\"', temp, &start, &len);
			len = 0;
		}
		if (temp[start + len] == '\'')
		{
			len++;
			temp = trim_quotation_marks('\'', temp, &start, &len);
			len = 0;
		}	
		if (temp[start + len] == '$')
		{
			if (ft_strchr("'?'' ''\0'", temp[start + len + 1]))
				len++;
			else
				temp = expansion(base, temp, &start, &len);
		}
			
		start++;
	}
	return (temp);
}

static int	create_list_item(t_base *base, char *line,
								size_t *len, unsigned int start)
{
	char	*temp;
	int		check;

	temp = NULL;
	check = 0;
	temp = ft_substr((char const *)line, start, *len);
	temp = check_expansion(base, temp, 0, 0);
	if (temp)
		ft_list_push_back(&base->list, temp);
	if (line[start + *len] != '\0')
		start += *len;
	else
		start += *len - 1;
	*len = 0;
	return (start);
}

static void	check_missing_q_two(char *temp, unsigned int *start, size_t *len, char type)
{
	(*len)++;
	while (temp[*start + *len] != type && temp[*start + *len] != '\0')
		(*len)++;
	if (temp[*start + *len] != type)
		error_handler("missing quotation marks\n", NULL, NULL, 2);
	(*len)++;

}

static void	check_missing_q(char *temp, unsigned int *start, size_t *len)
{
	while (temp[*start + *len] != '\0')
	{
		if (temp[*start + *len] == '\'')
		{
			check_missing_q_two(temp, start, len, '\'');
			if (temp[*start + *len] == ' ' || temp[*start + *len] == '\0')
				break;
		}
		else if (temp[*start + *len] == '\"')
		{
			check_missing_q_two(temp, start, len, '\"');
			if (temp[*start + *len] == ' ' || temp[*start + *len] == '\0')
				break;
		}
		(*len)++;
	}
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
			error_handler("error near unexpected token`>'\n", base->list, NULL, 258);
		if (line[start + len] == '\'' || line[start + len] == '\"')
			check_missing_q(line, &start, &len);
		if (ft_strchr("'|''<''>'';'' ''\0'", line[start + len]))
		{
			if (len != 0)
				start = create_list_item(base, line, &len, start);
		}
		if (line[start + len] == '>')
			handle_redirection(base, line, &len, &start);
		if ((line[start + len] == ';' && line[start + len + 1] != ';')|| line[start + len] == '|')
			ft_list_push_back(&base->list, ft_substr(line, start + len, 1));
		start++;
	}
}
