/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 11:37:51 by rixt          #+#    #+#                 */
/*   Updated: 2021/04/22 12:10:12 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**fill_array(char **array, int count, t_list *current)
{
	int		i;

	array = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		array[i] = (char *)current->content;
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**list_to_array(t_list *list)
{
	int		count;
	char	**array;
	t_list	*current;

	array = NULL;
	if (!list || !(list->content))
	{
		array = (char **)malloc(sizeof(char *));
		array[0] = NULL;
		return (array);
	}
	current = list;
	count = 0;
	while (current)
	{
		current = current->next;
		count++;
	}
	current = list;
	array = fill_array(array, count, current);
	return (array);
}

char	**make_path_array(char **envp)
{
	char	**pre_paths;
	char	**paths;
	char	**tmp;

	paths = NULL;
	tmp = envp;
	while (*tmp)
	{
		if (ft_strncmp("PATH=", *tmp, 5) == 0)
		{
			pre_paths = ft_split(*tmp, '=');
			paths = ft_split(pre_paths[1], ':');
			free_array(pre_paths);
		}
		tmp++;
	}
	return (paths);
}
