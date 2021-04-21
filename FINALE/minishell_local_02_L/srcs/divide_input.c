/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/21 14:01:27 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		expansion(t_base *base, char *temp, int start, int *len)
{
	int count;

	count = 0;
	while (base->env[count])
	{
		if (ft_strncmp(base->env[count], &temp[start], *len) == 0
				&& base->env[count][*len] == '=')
		{
			printf("ja");
			// str = enter_expansion(str, &start, &*len, base->env[count]);
			count = 0;
			break ;
		}
		count++;
	}
	start += *len;
	*len = 0;
	return (start);
}



static char	*check_expansion(t_base *base, char *temp, int len)
{
	int start;

	start = 0;
	while (temp[start + len] != '\0')
	{
		// if (temp[len] == '\"')
		// 	len = trim_and_exp(temp, len);
		// if (temp[len] == '\'')
		// 	len = trim_quotation_marks(temp, len);
		if (temp[start + len] == '$')
		{
			while (temp[start + len] != '\0' || temp[len] != '$' || temp[len] != '\'' || temp[len] != '\"')
				len++;
			temp = expansion(base, temp, start, &len);
		}
			
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
			check_solo++;
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
	temp = check_expansion(base, temp, len);
	printf("temp: %s\n", temp);
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
