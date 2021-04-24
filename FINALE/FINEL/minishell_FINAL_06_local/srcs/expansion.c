/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/22 15:56:32 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/24 17:40:25 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_str(char *str, char *str_temp, char *str_end)
{
	free(str);
	str = ft_strjoin(str_temp, str_end);
	return (str);
}

static char	*trim_quotation_marks(char type, char *str,
	unsigned int *start, size_t *len)
{
	char	*str_start;
	char	*str_end;
	char	*str_temp;
	char	*loose;

	loose = NULL;
	str_start = NULL;
	str_temp = NULL;
	str_end = NULL;
	loose = ft_substr(str, *start, *len);
	if (*start > 1)
		str_start = ft_substr(str, 0, (size_t)(*start) - 1);
	else
		str_start = ft_strdup("");
	if (*start + ft_strlen(loose) < ft_strlen(str) - 2)
		str_end = ft_substr(str, *start + ft_strlen(loose) + 1,
				ft_strlen(str) - 2);
	else
		str_end = ft_strdup("");
	str_temp = ft_strjoin(str_start, loose);
	str = create_str(str, str_temp, str_end);
	set_start_len(str_start, loose, start, type);
	int i = 0;
	while (loose[i] != '\0' && loose[i] != '$' && type == '\"' && str_end[0] != '\0')
		i++;
	*len = 0;
	while (loose[i + *len] != '\0' && type == '\"' && str_end[0] != '\0')
		(*len)++;
	if (loose[i + *len] == '\0' && type == '\"' && str_end[0] != '\0')
		(*len)--;
	if (*len > 0 && str_start[0] != '\0' && type == '\"')
		*start = ft_strlen(str_start);	
	free_all(str_start, str_end, str_temp, loose);
	return (str);
}

static char	*prep_trim_quotation_marks(char type, char *temp,
	size_t *len, unsigned int *start)
{
	(*start)++;
	while (!ft_strchr(&type, temp[*start + *len]))
		(*len)++;
	if (*len == 0)
	{
		free(temp);
		temp = ft_strdup("");
		return (temp);
	}
	temp = trim_quotation_marks(type, temp, start, len);
	return (temp);
}

static char	*prep_expansion(t_base *base, char *temp,
	size_t *len, unsigned int *start)
{
	if (ft_strchr("'?'' ''\0'", temp[*start + *len + 1]))
		(*len)++;
	else
	{
		(*start)++;
		temp = expansion(base, temp, start, len);
	}
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
			temp = prep_trim_quotation_marks('\"', temp, &len, &start);
		if (temp[start + len + minus] == '\'')
			temp = prep_trim_quotation_marks('\'', temp, &len, &start);
		if (temp[start + minus] == '$')
		{
			temp = prep_expansion(base, temp, &len, &start);
			if (temp == NULL)
				break ;
			if (start == 0 || ft_strchr("'$''\'''\"'", temp[start + len]))
				minus = -1;
		}
		start++;
	}
	return (temp);
}
