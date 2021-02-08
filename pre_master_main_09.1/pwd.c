/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/03 14:34:51 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        pwd(int fd)
{
    char *path;

    path = getcwd(NULL, 0);
    if (path == NULL)
        error_handler("pwd failure", NULL, NULL); //veranderen met geheugen;
    path = ft_strjoin(path, "\n");
    if (write(fd, path, ft_strlen(path)) < 0)
        printf("error\n");
    	free(path);
    path = NULL;
}