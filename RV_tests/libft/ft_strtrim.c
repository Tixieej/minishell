/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:48:44 by rde-vrie      #+#    #+#                 */
/*   Updated: 2019/11/26 16:58:28 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char const *s1, char const *set, int end)
{
	size_t	i;
	int		start;

	i = 0;
	start = 0;
	while (set[i] != '\0' && start < end)
	{
		if (s1[start] == set[i])
		{
			start++;
			i = 0;
		}
		else
			i++;
	}
	return (start);
}

static int	ft_end(char const *s1, char const *set, int start, int end)
{
	size_t i;

	i = 0;
	while (set[i] != '\0' && start < end)
	{
		if (s1[end - 1] == set[i])
		{
			end--;
			i = 0;
		}
		else
			i++;
	}
	return (end);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		start;
	size_t	len;
	int		end;

	if (!s1)
		return (NULL);
	len = 0;
	end = ft_strlen(s1);
	start = ft_start(s1, set, end);
	end = ft_end(s1, set, start, end);
	if (end < start)
		return (NULL);
	len = end - start;
	trim = ft_substr(s1, start, len);
	return (trim);
}
