/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/18 14:40:25 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        pwd(t_command *command)
{
    char *path;

    path = getcwd(NULL, 0);
    if (path == NULL)
        error_handler("pwd failure", NULL, NULL); //veranderen met geheugen;
    path = ft_strjoin(path, "\n");
    if (write(STDOUT_FILENO, path, ft_strlen(path)) < 0)
        error_handler("pwd write error", NULL, command);
    free(path);
    path = NULL;
}