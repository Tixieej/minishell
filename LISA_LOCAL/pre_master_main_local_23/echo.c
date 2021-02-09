/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/21 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/09 13:14:07 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// modes : O_RDONLY, O_WRONLY, or O_RDWR.
void        echo(t_command *command)
{
    char *s;
    // t_command	*cur_struct;
    t_list      *cur_args;

    // cur_struct = command;
    cur_args = command->args;
    s = ft_strdup("");
    while (cur_args)
    {
        s = ft_strjoin(s, (const char *)cur_args->content);
        s = ft_strjoin(s, " ");
        cur_args = cur_args->next;
    }
    if (ft_strlen(s) == 0)
        s = ft_strdup("\n");
    else
        s[ft_strlen(s) - 1] = '\n';
    if (write(command->fd_out, s, ft_strlen(s)) < 0)
        printf("error\n");
    cur_args = command->args;
    free(s);
    s = NULL;
    return;
}
