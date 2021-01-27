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
    int fd;
    char *s;

    fd = 1;
    s = ft_strdup("");
    while (command->args)
    {
        s = ft_strjoin(s, (const char *)command->args->content);
        s = ft_strjoin(s, " ");
        command->args = command->args->next;
    }
    s[ft_strlen(s) - 1] = '\n';
    if (command->in_red)
        printf("overslaan?"); // later weghalen
    while (command->out_red)
    {
        if (!(ft_strncmp((const char *)command->out_red->content, ">>", 2)))
            command->out_red = command->out_red->next;
            if (command->out_red)
                fd = open((const char *)command->out_red->content, O_CREAT | O_RDWR | O_APPEND, 0644);
        else if (!(ft_strchr(">", (int)command->out_red->content)))
            command->out_red = command->out_red->next;
            if (command->out_red)
                fd = open((const char *)command->out_red->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (fd < 0)
            error_handler("open file failed\n");
        command->out_red = command->out_red->next;
    }
    if (write(fd, s, ft_strlen(s)) < 0)
        printf("error\n");
    free(s);
    s = NULL;
}