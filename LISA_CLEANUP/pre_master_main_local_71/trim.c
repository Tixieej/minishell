/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trim.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 11:26:44 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/12 11:27:37 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_singl_quotation_marks(char *temp, char *type, int len, int i)
{
	char	*temp_tr;

	temp_tr = NULL;
	while (!ft_strchr("';'' ''<''>'\''\0'", temp[len]))
			(len)++;
	while (temp[i] != '\0')
	{
		if (temp[i] == '\'')
		{
			if (i > 1)
			{
				type = ft_substr(temp, 0, i);
				len -= i;
			}
			temp_tr = ft_substr(temp, i + 1, len - 2);
			free(temp);
			if (type)
				temp = ft_strjoin(type, temp_tr);
			else
				temp = ft_strdup(temp_tr);
			free(temp_tr);
			free(type);
		}
		i++;
	}
	return (temp);
}

// char	*trim_double_quotation_marks(char *temp, char *type, int len, int i)
// {
// 	char	*temp_tr;

// 	temp_tr = NULL;
// 	while (!ft_strchr("';'' ''<''>'\"'\0'", temp[len]))
// 			(len)++;
// 	while (temp[i] != '\0')
// 	{
// 		if (temp[i] == '\"')
// 		{
// 			if (i > 1)
// 			{
// 				type = ft_substr(temp, 0, i);
// 				len -= i;
// 			}
// 			temp_tr = ft_substr(temp, i + 1, len - 2);
            
// 			free(temp);
// 			if (type)
// 				temp = ft_strjoin(type, temp_tr);
// 			else
// 				temp = ft_strdup(temp_tr);
// 			free(temp_tr);
// 			free(type);
// 		}
// 		i++;
// 	}
// 	return (temp);
// }
