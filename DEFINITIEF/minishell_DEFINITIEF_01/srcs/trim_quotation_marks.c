/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trim_quotation_marks.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/25 10:31:56 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/25 10:45:17 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_str(char *str, char *str_temp, char *str_end)
{
	free(str);
	str = ft_strjoin(str_temp, str_end);
	return (str);
}

static void	set_start_len_pt2(t_base *base, char *loose,
	unsigned int *start, size_t *len)
{
	int	i;

	i = 0;
	while (loose[i] != '\0' && loose[i] != '$' && base->type == '\"'
		&& base->str_end[0] != '\0')
		i++;
	*len = 0;
	while (loose[i + *len] != '$' && loose[i + *len + 1] != '\0'
		&& base->type == '\"' && base->str_end[0] != '\0'
		&& base->str_end[0] == '\'')
		(*len)++;
	while (loose[i + *len + 1] != '\0' && base->type == '\"'
		&& base->str_end[0] != '\0' && base->str_end[0] != '\''
		&& base->str_end[0] != '\"')
		(*len)++;
	if (*len > 0 && base->str_start[0] != '\0' && base->type == '\"')
		*start += ft_strlen(base->str_start);
}

void	set_start_len(char *str_start, char *loose,
	unsigned int *start, char type)
{
	int	len;

	len = 0;
	while (loose[len] != '\0' && loose[len] != '$' && type == '\"')
		len++;
	if (loose[len] != '$' && type == '\"')
		*start = ft_strlen(str_start) + ft_strlen(loose) - 1;
	if (loose[len] == '$' && type == '\"')
		*start = len;
	if (type == '\'')
		*start = ft_strlen(str_start) + ft_strlen(loose) - 1;
}

static char	*trim_quotation_marks(t_base *base, char *str,
	unsigned int *start, size_t *len)
{
	char	*loose;

	loose = NULL;
	loose = ft_substr(str, *start, *len);
	if (*start > 1)
		base->str_start = ft_substr(str, 0, (size_t)(*start) - 1);
	else
		base->str_start = ft_strdup("");
	if (*start + ft_strlen(loose) < ft_strlen(str) - 2)
		base->str_end = ft_substr(str, *start + ft_strlen(loose) + 1,
				ft_strlen(str) - 2);
	else
		base->str_end = ft_strdup("");
	base->str_temp = ft_strjoin(base->str_start, loose);
	str = create_str(str, base->str_temp, base->str_end);
	set_start_len(base->str_start, loose, start, base->type);
	set_start_len_pt2(base, loose, start, len);
	free_all(base->str_start, base->str_end, base->str_temp, loose);
	return (str);
}

char	*prep_trim_quotation_marks(t_base *base, char *temp,
	size_t *len, unsigned int *start)
{
	(*start)++;
	while (!ft_strchr(&base->type, temp[*start + *len]))
		(*len)++;
	if (*len == 0 && *start == 1)
	{
		free(temp);
		temp = ft_strdup("");
		return (temp);
	}
	temp = trim_quotation_marks(base, temp, start, len);
	return (temp);
}
