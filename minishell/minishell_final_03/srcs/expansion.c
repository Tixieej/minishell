/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/22 15:56:32 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/24 13:26:16 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_loose_dol(t_base *base, char *loose)
{
	int				len;
	char			*dol;
	char			*temp;
	t_exp			expval;

	set_exp_values(&expval);
	len = 0;
	dol = NULL;
	temp = NULL;
	(void)base;
	while (loose[len] != '\0' && loose[len] != '$')
		len++;
	if (loose[len] == '$')
	{
		expval.pre_dol = ft_strdup(&loose[len]);
		dol = expansion(base, expval.pre_dol, &(expval.start), &(expval.len));
	}
	if (dol)
	{
		temp = ft_substr(loose, 0, len);
		free(temp);
		free(loose);
		loose = ft_strjoin(temp, dol);
	}
	return (loose);
}

static char	*trim_quotation_marks(t_base *base, char *str,
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
	loose = check_loose_dol(base, loose);
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
	set_start_len(str_start, loose, start, base->type);
	free_all(str_start, str_end, str_temp, loose);
	return (str);
}

static char	*prep_trim_quotation_marks(t_base *base, char *temp,
	size_t *len, unsigned int *start)
{
	(*start)++;
	while (!ft_strchr(&base->type, temp[*start + *len]))
		(*len)++;
	if (*len == 0)
	{
		free(temp);
		temp = ft_strdup("");
		return (temp);
	}
	temp = trim_quotation_marks(base, temp, start, len);
	*len = 0;
	return (temp);
}

char	*prep_expansion(t_base *base, char *temp,
	size_t *len, unsigned int *start)
{
	if (ft_strchr("'?'' ''\0'", temp[*start + *len + 1]))
		(*len)++;
	else
	{
		if (*len > 0)
			*start += *len;
		if (*len > 0)
			*len = 0;
		(*start)++;
		temp = expansion(base, temp, start, len);
	}
	return (temp);
}

char	*check_expansion(t_base *base, char *temp,
	size_t len, unsigned int start)
{
	int	min;

	min = 0;
	while (temp[start + len + min] != '\0')
	{
		if (min == -1)
			start--;
		min = 0;
		if (temp[start + len + min] == '\"')
			base->type = '\"';
		if (temp[start + len + min] == '\'')
			base->type = '\'';
		if (temp[start + len + min] == '\'' || temp[start + len + min] == '\"')
			temp = prep_trim_quotation_marks(base, temp, &len, &start);
		if (temp[start + len + min] == '$')
		{
			temp = prep_expansion(base, temp, &len, &start);
			if (temp == NULL)
				break ;
			if (start == 0 || ft_strchr("'$''\'''\"'", temp[start + len]))
				min = -1;
		}
		start++;
	}
	return (temp);
}
