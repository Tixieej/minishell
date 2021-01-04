/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 10:03:31 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/02/27 16:18:49 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	*ft_free(char **array, int i)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
	return (NULL);
}

static int	ft_len(char const *s, char c)
{
	int len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

static int	ft_next_word(char const *s, char c)
{
	int start;

	start = 0;
	while (*s == c)
	{
		start++;
		s++;
	}
	return (start);
}

static char	**ft_fill(char const *s, char c, int count, char **array)
{
	int		j;
	int		len;
	int		i;

	i = 0;
	while (i < count)
	{
		s = &s[ft_next_word(s, c)];
		len = ft_len(s, c);
		array[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!array[i])
			return (ft_free(array, i));
		j = 0;
		while (j <= len)
		{
			array[i][j] = s[j];
			j++;
		}
		array[i][len] = '\0';
		s = &s[len];
		i++;
	}
	return (array);
}

char		**ft_split(char const *s, char c)
{
	char	**array;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	array[count] = NULL;
	array = ft_fill(s, c, count, array);
	return (array);
}
