/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/22 09:01:12 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*enter_expansion(char *str, int *start, int *len, char *env)
// {
// 	char	*str_end;
// 	char	*str_start;
// 	char	*exp;
// 	char	*temp;

// 	temp = NULL;
// 	str_end = NULL;
// 	if (env == NULL)
// 		str = remove_expansion(str, *start, *len);
// 	else
// 	{
// 		exp = ft_strdup(&env[*len + 1]);
// 		if (str[*start + *len] == '$')
// 			str_end = ft_strdup(&str[*start + *len]);
// 		if (str[0] == '\"')
// 			str_start = ft_substr(str, 1, *start - 2);
// 		else
// 			str_start = ft_substr(str, 0, *start - 1);
// 		temp = ft_strjoin(str_start, exp);
// 		*start += ft_strlen(exp) - 3;
// 		*len = 0;
// 		free(str);
// 		if (str_end)
// 			str = ft_strjoin(temp, str_end);
// 		else
// 			str = ft_strdup(temp);
// 		free(temp);
// 		free(str_end);
// 		free(str_start);
// 	}
// 	return (str);
// }

static char	*expansion(t_base *base, char *temp, int *start, size_t *len)
{
	int		count;
	char	*str_start;
	char	*str;

	str_start = ft_strdup("");
	count = 0;
	str = NULL;
	if (*start > 0)
		str_start = ft_substr(temp, 0, *start);
	while (base->env[count])
	{
		if (ft_strncmp(base->env[count], &temp[*start], *len) == 0
				&& base->env[count][*len] == '=')
		{
			temp = ft_strdup(&base->env[count][*len + 1]);
			count = 0;
			break ;
		}
		count++;
	}
	printf("str start %s\n", str_start);
	printf("str temp %s\n", temp);
	str = ft_strjoin(str_start, temp);
	free(temp);
	free(str_start);
	// *start += ft_strlen(temp);
	*len = 0;

	return (str);
}

static char	*check_expansion(t_base *base, char *temp, size_t len)
{
	int		start;
	char	*str_end;
	size_t	str_len;
	char	*str;

	str = NULL;	
	str_len = ft_strlen(temp);
	start = 0;
	str_end = ft_strdup("");
	while (temp[start + len] != '\0')
	{
		// if (temp[len] == '\"')
		// 	len = trim_and_exp(temp, len);
		// if (temp[len] == '\'')
		// 	len = trim_quotation_marks(temp, len);
		if (temp[start + len] == '$')
		{
			start++;
			while (temp[start + len] != '\0' && temp[start + len] != '$' && temp[start + len] != '\'' && temp[start + len] != '\"')
				len++;
			if (str_len > len)
				str_end = ft_strdup(&temp[start + len]);
			str = ft_strjoin(expansion(base, temp, &start, &len), str_end);
			free(temp);
			temp = ft_strdup(str);
			free(str);
		}
		len++;
	}
	return (temp);
}

static void	check_missing_q(char *temp, int	check_solo, int check_double)
{
	int len;

	len = 0;
	while (temp[len] != '\0')
	{
		if (temp[len] == '\'')
		{
			while (temp[len] != '\0')
			{
				if (temp[len] == '\'');
				check_solo++;
			}

		}
			
			
		if (temp[len] == '\"')
			check_double++;
		len++;
	}
	if ((check_solo & 1) == 1 || (check_double & 1) == 1)
		error_handler("missing quotation marks\n", NULL, NULL, 2);
}

static int	create_list_item(t_base *base, char *line,
								size_t *len, unsigned int start)
{
	char	*temp;
	int		check;

	temp = NULL;
	check = 0;
	temp = ft_substr((char const *)line, start, *len);
	check_missing_q(temp, 0, 0);
	temp = check_expansion(base, temp, 0);
	// printf("temp: %s\n", temp);
	if (temp)
		ft_list_push_back(&base->list, temp);
	if (line[start + *len] != '\0')
		start += *len;
	else
		start += *len - 1;
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

void	divide_input(t_base *base, char *line,
							size_t len, unsigned int start)
{
	while (line[start + len] != '\0')
	{
		while (line[start + len] == ' ')
			start++;
		if (!ft_strchr("'|'';'' ''<''>''\0'", line[start + len])
			|| line[start + len] =='\'')
		{
			while (!ft_strchr("'|'';'' ''<''>''\0'", line[start + len])
				|| line[start + len] =='\'')
				len++;		
		}
		if (!ft_strncmp(&line[start + len], ">>>", 3))
			error_handler("error near unexpected token`>'\n", base->list, NULL, 258);
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
