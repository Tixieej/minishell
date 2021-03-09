/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/09 13:36:12 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_command *command)
{
	char	*path;
	char	*old_path;

	path = NULL;
	old_path = getcwd(NULL, 0);
	if (old_path == NULL)
		error_handler("pwd failure", NULL, command);
	path = ft_strjoin(old_path, "\n");
	if (write(STDOUT_FILENO, path, ft_strlen(path)) < 0)
		error_handler("pwd write error", NULL, command);
	free(old_path);
	free(path);
	path = NULL;
}
