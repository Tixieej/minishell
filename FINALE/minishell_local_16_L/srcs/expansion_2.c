/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/22 17:54:55 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/23 13:38:10 by livlamin      ########   odam.nl         */
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
	free(str_start);
	free(str_end);
	free(str_temp);
	free(env);
	return (str);
}

char	*expansion(t_base *base, char *temp,
	unsigned int *start, size_t *len)
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
			break ;
		}
		count++;
	}
	temp = enter_expansion(temp, start, len, expansion);
	return (temp);
}
