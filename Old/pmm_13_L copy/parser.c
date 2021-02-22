/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/15 16:34:24 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void     add_semicolon(t_list **cur_lst, t_command **cur_struct)
{
    ft_struct_push_back(&(*cur_struct), (char *)(*cur_lst)->content);
}

static void     add_pipe(t_list **cur_lst, t_command **cur_struct, char **env, t_fds *backups)
{
    (*cur_struct)->pipe_right = 1;
    (*cur_lst) = (*cur_lst)->next;
	check_type(env, *cur_struct, backups);
    ft_struct_push_back(&(*cur_struct), (char *)(*cur_lst)->content);
	(*cur_struct)->next->pipe_in = (*cur_struct)->pipe_in;
	(*cur_struct)->next->pipe_out = (*cur_struct)->pipe_out;
	cur_struct = &(*cur_struct)->next;
    (*cur_struct)->pipe_left = 1;
}

static void     add_redirection(t_list **cur_lst, t_command **cur_struct)
{
    if (*(*cur_lst)->content == '>')
    {
        ft_list_push_back(&(*cur_struct)->out_red, ft_strdup((*cur_lst)->content));
        (*cur_lst) = (*cur_lst)->next;
        if (*cur_lst)
            ft_list_push_back(&(*cur_struct)->out_red, ft_strdup((*cur_lst)->content));
    }
    if (*(*cur_lst)->content == '<')
    {
        ft_list_push_back(&(*cur_struct)->in_red, ft_strdup((*cur_lst)->content));
        (*cur_lst) = (*cur_lst)->next;
        if (*cur_lst)
            ft_list_push_back(&(*cur_struct)->in_red, ft_strdup((*cur_lst)->content));
    }
}

void            parser(t_list **list, char **env, t_command *command)
{
    t_list      *cur_lst;
    t_command   **cur_struct;
	t_fds 		backups;
	
    cur_lst = *list;
    cur_struct = &command;
    ft_struct_push_back(&command, (char *)cur_lst->content);
    cur_lst = cur_lst->next;
    while (cur_lst)
    {
        if (*cur_lst->content == ';')
        {
            check_type(env, *cur_struct, &backups);
            cur_lst = cur_lst->next;
            add_semicolon(&cur_lst, cur_struct);
            cur_struct = &(*cur_struct)->next;
        }
        else if (*cur_lst->content == '|')
        {
            add_pipe(&cur_lst, cur_struct, env, &backups);
            cur_struct = &(*cur_struct)->next;
        }
        else if (*cur_lst->content == '>' || *cur_lst->content == '<')
            add_redirection(&cur_lst, cur_struct);
        else
            ft_list_push_back(&(*cur_struct)->args, ft_strdup((char *)(*cur_lst).content));
        cur_lst = cur_lst->next;
    }
    cur_lst = *list; // weg?
    //print_cur_struct(command); // weg !!
    check_type(env, *cur_struct, &backups);
	close((*cur_struct)->pipe_in);
	close((*cur_struct)->pipe_out);
	dup2(backups.stout, STDOUT_FILENO);
	dup2(backups.stin, STDIN_FILENO);
    cur_struct = &command;
	//ft_clear_linked_struct(command);  //werkt met exec
}