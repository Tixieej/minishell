/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/21 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/08 10:26:33 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// modes : O_RDONLY, O_WRONLY, or O_RDWR.
void        echo(t_command *command)
{
    char *s;
    t_command	**cur_struct;

    cur_struct = &command;
    s = ft_strdup("");
    while ((*cur_struct)->args)
    {
        s = ft_strjoin(s, (const char *)(*cur_struct)->args->content);
        s = ft_strjoin(s, " ");
        (*cur_struct)->args = (*cur_struct)->args->next;
    }
    if (ft_strlen(s) == 0)
        s = ft_strdup("\n");
    else
        s[ft_strlen(s) - 1] = '\n';
    if (write(command->fd_stdout, s, ft_strlen(s)) < 0)
        printf("error\n");
    free(s);
    s = NULL;
    return;
}
