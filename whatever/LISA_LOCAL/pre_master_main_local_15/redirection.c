/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/21/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/21/01 15:55:26 by livlamin          ########   odam.nl     */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//LET OP CLOSEN!!

int    redirection(t_command *command)
{
    int fd;
    t_command	**cur_struct;

    cur_struct = &command;
    fd = 1;
    if ((*cur_struct)->in_red)
        fd = open((const char *)(*cur_struct)->out_red->content, O_RDONLY, 0644);
    while ((*cur_struct)->out_red)
    {
        if (!(ft_strncmp((const char *)(*cur_struct)->out_red->content, ">>", 2)))
        {
            (*cur_struct)->out_red = (*cur_struct)->out_red->next;
            if ((*cur_struct)->out_red)
                fd = open((const char *)(*cur_struct)->out_red->content, O_CREAT | O_RDWR | O_APPEND, 0644);
        }
        else if ((ft_strchr(">", (int)(*cur_struct)->out_red->content)))
        {
            (*cur_struct)->out_red = (*cur_struct)->out_red->next;
            if ((*cur_struct)->out_red)
                fd = open((const char *)(*cur_struct)->out_red->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
        }
        if (fd < 0)
            error_handler("open file failed\n", NULL, (*cur_struct));
        (*cur_struct)->out_red = (*cur_struct)->out_red->next;
    }
    if (fd < 0)
        error_handler("open file failed\n", NULL, NULL); //checken
    return (fd);
}