/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 13:16:00 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/08 10:32:32 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//LET OP CLOSEN!!

void    in_red(t_command *command)
{
    t_command	**cur_struct;

    cur_struct = &command;
    while ((*cur_struct)->in_red)
    {
        if (!(ft_strncmp((const char *)(*cur_struct)->out_red->content, "<", 1)))
        {
            (*cur_struct)->in_red = (*cur_struct)->in_red->next;
            if ((*cur_struct)->in_red)
                command->fd_stdin = open((const char *)(*cur_struct)->out_red->content, O_RDONLY, 0644);
        }
        if (command->fd_stdin < 0)
            error_handler("open file failed\n", NULL, NULL); //checken
        (*cur_struct)->in_red = (*cur_struct)->in_red->next;
    }
}

void    out_red(t_command *command)
{
    t_command	**cur_struct;

    cur_struct = &command;
    while ((*cur_struct)->out_red)
    {
        if (!(ft_strncmp((const char *)(*cur_struct)->out_red->content, ">>", 2)))
        {
            (*cur_struct)->out_red = (*cur_struct)->out_red->next;
            if ((*cur_struct)->out_red)
                command->fd_stdout = open((const char *)(*cur_struct)->out_red->content, O_CREAT | O_RDWR | O_APPEND, 0644);
        }
        else if (!(ft_strncmp((const char *)(*cur_struct)->out_red->content, ">", 1)))
        {
            (*cur_struct)->out_red = (*cur_struct)->out_red->next;
            if ((*cur_struct)->out_red)
                command->fd_stdout = open((const char *)(*cur_struct)->out_red->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
        }
        if (command->fd_stdout < 0)
            error_handler("open file failed\n", NULL, (*cur_struct));
        (*cur_struct)->out_red = (*cur_struct)->out_red->next;
    }
}


void    redirection(t_command *command)
{
    t_command	**cur_struct;

    cur_struct = &command;
    command->fd_stdin = 1; //klopt dit?
    command->fd_stdout = 1;
    in_red(command);
    out_red(command);
    return; //kan die weg?
}