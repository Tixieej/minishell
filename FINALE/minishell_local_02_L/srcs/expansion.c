/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/19 13:11:32 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/21 12:38:54 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*trim_dq(char	*str)
// {
// 	char	*temp;

// 	temp = ft_substr(str, 1, ft_strlen(str) - 1);
// 	free(str);
// 	return (temp);
// }

// static char	*remove_expansion(char *str, int start, int len)
// {
// 	char	*str_end;
// 	char	*str_start;

// 	str_start = ft_substr(str, 0, start - 1);
// 	str_end = ft_strdup(&str[start + 1 + len]);
// 	free(str);
// 	str = ft_strjoin(str_start, str_end);
// 	free(str_start);
// 	free(str_end);
// 	return (str);
// }

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


// char	*check_exp_within_dq(char **env, char *str, int start, int count)
// {
// 	int	len;
// 	int	check;

// 	check = 0;
// 	len = 0;
// 	while (str[start + len] != '\0' && str[start + len] != '\'')
// 	{
// 		if (str[start + len] == '$' && str[start + len + 1] != '\0')
// 		{
// 			start += len + 1;
// 			len = 0;
// 			while (str[start + len] != '\0' && str[start + len] != '$'
// 				&& str[start + len] != '\"' && ft_isalpha(str[start + len]) == 1)
// 				len++;
// 			while (env[count])
// 			{
// 				if (ft_strncmp(env[count], &str[start], len) == 0
// 					&& env[count][len] == '=')
// 				{
// 					check = 1;
// 					str = enter_expansion(str, &start, &len, env[count]);
// 					count = 0;
// 					break ;
// 				}
// 				count++;
// 			}
// 			if (check != 1)
// 				str = enter_expansion(str, &start, &len, NULL);
// 		}
// 		len++;
// 	}
// 	if (str[0] == '\"' || str[0] == '\'')
// 		str = trim_dq(str);
// 	return (str);
// }
