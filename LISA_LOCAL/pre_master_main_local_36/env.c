/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 11:38:21 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/09 10:52:42 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_result(t_command *command, char **env, int *check, int len)
{
	int		times;
	char	*temp;
	char	*result;

	temp = NULL;
	times = 0;
	result = ft_strdup("");
	while (env[times] != NULL)
	{
		temp = ft_strjoin(result, env[times]);
		free(result);
		result = ft_strjoin(temp, "\n");
		free(temp);
		temp = NULL;
		if (len > 0)
		{
			if (ft_strncmp(env[times], command->args->content, len) == 0)
			{
				if (command->args->content[len - 1] == '=')
					(*check)++;
			}
		}
		times++;
	}
	return (result);
}

void	env_check(t_command *command, char **env, int len)
{
	char	*result;
	int		check;

	check = 0;
	result = NULL;
	if (command->args)
		len = ft_strlen(command->args->content);
	result = create_result(command, env, &check, len);
	if (check == 1 || (check == 0 && len == 0))
		printf("%s", result);
	else
		printf("env: %s: No such file or directory\n", (char *)command->args->content);      
	free (result);
	result = NULL;
	return ;
}
