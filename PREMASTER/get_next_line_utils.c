/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 16:44:21 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/02/11 10:09:37 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*gnl_strcpy(char *join, char *s1, char *s2, int n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && j < n)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2, int n)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
	{
		free(s1);
		return (NULL);
	}
	join = gnl_strcpy(join, s1, s2, n);
	free(s1);
	return (join);
}

int		gnl_strchr(char *s, char c)
{
	int pos;

	pos = 0;
	while (s[pos] != '\0' && s[pos] != c)
		pos++;
	if (s[pos] == '\0')
		return (-1);
	return (pos);
}
