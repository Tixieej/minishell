/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 11:00:29 by livlamin      #+#    #+#                 */
/*   Updated: 2019/12/03 12:44:39 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_begin(char *s1, char *set)
{
	int i;
	int len;

	i = 0;
	len = (int)ft_strlen(set);
	while (ft_memchr(set, s1[i], len) != NULL && s1[i])
	{
		i++;
	}
	return (i);
}

static int		ft_end(char *s1, char *set)
{
	int len;
	int	i;

	len = (int)ft_strlen(s1);
	i = 0;
	while (len > 0 && ft_strchr(set, s1[len - 1]) != NULL)
	{
		len--;
		i++;
	}
	return (i);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*temp;
	int		begin;
	int		end;
	int		len;
	int		i;

	i = 0;
	if (*set == '\0')
		return (ft_strdup((char *)s1));
	begin = ft_begin((char *)s1, (char *)set);
	end = ft_end((char *)s1, (char *)set);
	len = (int)ft_strlen((char *)s1) - begin - end;
	if (len <= 0)
		return (ft_strdup(""));
	temp = (char *)malloc(sizeof(char) * len + 1);
	if (!temp)
		return (NULL);
	while (len > i)
	{
		temp[i] = s1[begin];
		begin++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
