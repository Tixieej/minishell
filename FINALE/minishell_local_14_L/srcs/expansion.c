/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/22 15:56:32 by livlamin      #+#    #+#                 */
/*   Updated: 2021/04/23 13:16:08 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all(char *str_start, char *str_end,
	char *str_temp, char *loose)
{
	free(str_start);
	free(str_end);
	free(str_temp);
	free(loose);
}

static void	set_start_len(char *str_start, char *loose,
	unsigned int *start, char type)
{
	if (type == '\'')
		*start = ft_strlen(str_start) + ft_strlen(loose);
	if (type == '\"')
		*start = ft_strlen(str_start);
	if (*start > 0)
		(*start)--;
}

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
	while (!ft_strchr("type'\0'", str[*start + *len]))
		(*len)++;
	loose = ft_substr(str, *start + 1, *len - 2);
	if (*start > 1)
		str_start = ft_substr(str, 0, (size_t)(*start));
	else
		str_start = ft_strdup("");
	if (*start + ft_strlen(loose) < ft_strlen(str) - 2)
		str_end = ft_substr(str, *start + ft_strlen(loose) + 1, ft_strlen(str) - 2);
	else
		str_end = ft_strdup("");
	str_temp = ft_strjoin(str_start, loose);
	str = create_str(str, str_temp, str_end);
	set_start_len(str_start, loose, start, type);
	free_all(str_start, str_end, str_temp, loose);
	return (str);
}

char	*check_expansion(t_base *base, char *temp,
	size_t len, unsigned int start)
{
	while (temp[start + len] != '\0')
	{
		if (temp[start + len] == '\"')
		{
			len++;
			temp = trim_quotation_marks('\"', temp, &start, &len);
			len = 0;
		}
		if (temp[start + len] == '\'')
		{
			len++;
			temp = trim_quotation_marks('\'', temp, &start, &len);
			len = 0;
		}	
		if (temp[start + len] == '$' || temp[start + len - 1] == '$')
		{
			if (temp[start + len - 1] == '$')
				start--;
			if (ft_strchr("'?'' ''\0'", temp[start + len + 1]))
				len++;
			else
				temp = expansion(base, temp, &start, &len);
			if (temp[0] == '\0')
				break;
			if (temp[start + len + 1] == '\0')
				break;
		}
		start++;
	}
	return (temp);
}
