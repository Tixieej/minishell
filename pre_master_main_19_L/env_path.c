/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 16:29:08 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/15 09:38:49 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_array(t_list **list)
{
	int		count;
	char	**array;
	int		i;
	t_list	*current;

	if (!(*list) || !((*list)->content))// klopt dit?
	{
		array = (char **)malloc(sizeof(char *));
		array[0] = NULL;
		return (array);
	}
	current = *list;
	count = 0;
	while (current)// misschien met list lopen maar dan met de kopie begin;
	{
		current = current->next; //
		count++;
	}
	array = (char **)malloc(sizeof(char *) * (count + 1)); //wordt gefreed in ft_exec
	i = 0;
	current = *list;
	while (i < count)
	{
		array[i] = (char *)current->content;
		current = current->next;
		i++;
	}
	array[i] = NULL;
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
