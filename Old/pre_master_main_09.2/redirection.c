/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 13:16:00 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/09 10:21:46 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//LET OP CLOSEN!!

int    in_red(t_command *command)
{
    t_command	**cur_struct;

    cur_struct = &command;
    while ((*cur_struct)->in_red)
    {
        if (!(ft_strncmp((const char *)(*cur_struct)->in_red->content, "<", 1)))
        {
            (*cur_struct)->in_red = (*cur_struct)->in_red->next;
            if ((*cur_struct)->in_red)
                command->fd_in = open((const char *)(*cur_struct)->in_red->content, O_RDONLY, 0644);
        }
        if (command->fd_in < 0)
            error_handler("open file failed\n", NULL, NULL); //checken
        (*cur_struct)->in_red = (*cur_struct)->in_red->next;
    }
	return (command->fd_in);
}

int    out_red(t_command *command)
{
    t_command	**cur_struct;

    cur_struct = &command;
    while ((*cur_struct)->out_red)
    {
        if (!(ft_strncmp((const char *)(*cur_struct)->out_red->content, ">>", 2)))
        {
            (*cur_struct)->out_red = (*cur_struct)->out_red->next;
            if ((*cur_struct)->out_red)
                command->fd_out = open((const char *)(*cur_struct)->out_red->content, O_CREAT | O_RDWR | O_APPEND, 0644);
        }
        else if (!(ft_strncmp((const char *)(*cur_struct)->out_red->content, ">", 1)))
        {
            (*cur_struct)->out_red = (*cur_struct)->out_red->next;
            if ((*cur_struct)->out_red)
                command->fd_out = open((const char *)(*cur_struct)->out_red->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
			printf("\tfile geopend, fd = [%d]\n", command->fd_out);
        }
        if (command->fd_out < 0)
            error_handler("open file failed\n", NULL, (*cur_struct));
        (*cur_struct)->out_red = (*cur_struct)->out_red->next;
    }
	return (command->fd_out);
}

void    redirection(t_command *command)
{
    t_command	**cur_struct;

    cur_struct = &command;
    command->fd_in = 0; //klopt dit?
    command->fd_out = 1;
    command->fd_in = in_red(command);
    command->fd_out = out_red(command);
	printf("\tfd_out = [%d]\n", command->fd_out);
    return; //kan die weg?
}