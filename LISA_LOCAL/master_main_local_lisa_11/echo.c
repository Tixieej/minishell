/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/21/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/21/01 15:55:26 by livlamin          ########   odam.nl     */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// modes : O_RDONLY, O_WRONLY, or O_RDWR.
void        echo(t_command *command)
{
    // command->args moet met een spatie minder
    int fd;

    // if file doesnt exist && TRUNC
    // fd = open("test", O_CREAT | O_RDWR | O_TRUNC, 0644);
    fd = open("test", O_CREAT | O_RDWR | O_APPEND, 0644);
    command->args = ft_strjoin(command->args, "\n");
    if (write(fd, command->args, ft_strlen(command->args)) < 0)
        printf("error\n");
    // printf("%s\n", command->args);
    // printf("echo\n");
}