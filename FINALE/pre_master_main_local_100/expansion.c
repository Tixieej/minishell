/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/19 13:11:32 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/19 13:12:06 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trim_dq(char	*str)
{
	char	*temp;

	temp = ft_substr(str, 1, ft_strlen(str) - 1);
	free(str);
	return (temp);
}

static char	*enter_expansion(char *str, int *start, int *len, char *env)
{
	char	*str_end;
	char	*str_start;
	char	*exp;
	char	*temp;

	temp = NULL;
	str_end = NULL;
	exp = ft_strdup(&env[*len + 1]);
	if (str[*start + *len] == '$')
		str_end = ft_strdup(&str[*start + *len]);
	str_start = ft_substr(str, 1, *start - 2);
	temp = ft_strjoin(str_start, exp);
	*start += ft_strlen(exp) - 3;
	*len = 0;
	free(str);
	if (str_end)
		str = ft_strjoin(temp, str_end);
	else	
		str = ft_strdup(temp);
	free(temp);
	free(str_end);
	free(str_start);
	return (str);
}

char	*check_exp_within_dq(t_base *base, char *str, int start, int count)
{
	int	len;

	len = 0;
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
				if (ft_strncmp(base->env[count], &str[start], len) == 0 && base->env[count][len] == '=')
				{
					printf("env: %c\n", base->env[count][len]);
					str = enter_expansion(str, &start, &len, base->env[count]);
					count = 0;
					break;
				}
				count++;
			}
		}
		len++;
	}
	if (str[0] == '\"' || str[0] == '\'')
		str = trim_dq(str);
	return (str);
}