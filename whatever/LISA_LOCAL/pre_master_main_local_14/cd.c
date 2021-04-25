/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/21/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/21/01 15:55:26 by livlamin          ########   odam.nl     */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        cd(t_command *command)
{
    char *path;

    path = getcwd(NULL, 0);
    int chdir(const char *path);
    printf("%s\n", path);
   printf("%s\n", command->program);
}