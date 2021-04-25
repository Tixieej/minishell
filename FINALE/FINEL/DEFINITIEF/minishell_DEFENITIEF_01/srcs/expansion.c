/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/22 15:56:32 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/25 10:40:40 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prep_expansion(t_base *base, char *temp,
	size_t *len, unsigned int *start)
{
	if (ft_strchr("'?''%'' ''\0'", temp[*start + *len + 1]))
		(*len)++;
	else
	{
		(*start)++;
		temp = expansion(base, temp, start, len);
	}
	*start += *len;
	*len = 0;
	return (temp);
}

char	*check_expansion(t_base *base, char *temp,
	size_t len, unsigned int start)
{
	int	minus;

	minus = 0;
	while (temp[start + len + minus] != '\0')
	{
		if (minus == -1)
			start--;
		minus = 0;
		if (temp[start + len + minus] == '\"')
			base->type = '\"';
		if (temp[start + len + minus] == '\'')
			base->type = '\'';
		if (temp[start + len] == '\'' || temp[start + len] == '\"')
			temp = prep_trim_quotation_marks(base, temp, &len, &start);
		if (temp[start + minus] == '$')
		{
			temp = prep_expansion(base, temp, &len, &start);
			if (temp == NULL)
				break ;
			if (start == 0 || ft_strchr("\"''\'''$'", temp[start + len]))
				minus = -1;
		}
		start++;
	}
	return (temp);
}
