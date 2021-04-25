/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/22 17:54:55 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/25 10:33:02 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*enter_expansion(char *str, unsigned int *start,
	size_t *len, char *env)
{
	char	*str_start;
	char	*str_end;
	char	*str_temp;

	str_start = NULL;
	str_temp = NULL;
	str_end = NULL;
	if (*start > 1)
		str_start = ft_substr(str, 0, (size_t)(*start) - 1);
	else
		str_start = ft_strdup("");
	if (*start + *len < ft_strlen(str))
		str_end = ft_strdup(&str[*start + *len]);
	else
		str_end = ft_strdup("");
	str_temp = ft_strjoin(str_start, env);
	free(str);
	str = ft_strjoin(str_temp, str_end);
	*len = 0;
	*start = ft_strlen(str_start) + ft_strlen(env);
	if (*start > 1)
		(*start)--;
	free_all(str_start, str_end, str_temp, env);
	return (str);
}

static void	set_len(char *temp, unsigned int *start, size_t *len)
{
	if (ft_strchr("'0''1''2''3''4''5''6''7''8''9'", temp[*start + *len]))
		(*len)++;
	else
		while (!ft_strchr("'\"''$''@''%''#''*''\'''-''\0'", temp[*start + *len]))
			(*len)++;
	if (temp[*start + *len] == '@')
		(*len)++;
}

char	*expansion(t_base *base, char *temp,
	unsigned int *start, size_t *len)
{
	int		count;
	char	*expansion;

	count = 0;
	expansion = ft_strdup("");
	if (*len == 0)
		set_len(temp, start, len);
	while (base->env[count])
	{
		if (ft_strncmp(base->env[count], &temp[*start], *len) == 0
			&& base->env[count][*len] == '=')
		{
			free(expansion);
			expansion = ft_strdup(&base->env[count][*len + 1]);
			break ;
		}
		count++;
	}
	temp = enter_expansion(temp, start, len, expansion);
	return (temp);
}
