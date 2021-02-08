/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/19 10:02:17 by livlamin      #+#    #+#                 */
/*   Updated: 2019/11/28 12:34:15 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_times(char const *s, char c)
{
	int i;
	int times;

	times = 0;
	i = 0;
	if (s[i] != c && s[i] != '\0')
		times = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			times++;
		i++;
	}
	return (times);
}

static char		**ft_free(char **result, int x)
{
	x--;
	while (x >= 0)
	{
		free(result[x]);
		x--;
	}
	free(result);
	return (NULL);
}

static char		**ft_to_fill(char **result, char const *s, char c)
{
	int index;
	int words;
	int mem;

	words = 0;
	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c)
		{
			mem = index;
			while (s[index] != c && s[index] != '\0')
			{
				index++;
			}
			result[words] = ft_substr(s, mem, (index - mem));
			if (!result[words])
				return (ft_free(result, words));
			words++;
		}
		if (s[index] != 0)
			index++;
	}
	return (result);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		times;

	times = ft_times(s, c);
	result = (char **)malloc(sizeof(char *) * (times + 1));
	if (!result)
		return (NULL);
	result[times] = NULL;
	if (times == 0)
		return (result);
	result = ft_to_fill(result, s, c);
	return (result);
}
