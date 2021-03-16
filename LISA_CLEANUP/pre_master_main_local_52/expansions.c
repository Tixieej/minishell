/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 11:38:21 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/16 15:29:34 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// t_list		*cur_args;
	// t_list		*cur_in_red;
	// t_list		*cur_out_red;
	// t_command	*temp;

	// while (command)
	// {
	// 	cur_args = command->args;
	// 	cur_in_red = command->in_red;
	// 	cur_out_red = command->out_red;
	// 	if ((command)->program)
	// 		free(command->program);
	// 	if (cur_args)
	// 		ft_lstclear(&cur_args, free);
	// 	if (cur_in_red != NULL)
	// 		ft_lstclear(&cur_in_red, free);
	// 	if (cur_out_red)
	// 		ft_lstclear(&cur_out_red, free);
	// 	temp = command;
	// 	command = command->next;
	// 	free(temp);
	// }

void    expansions(t_command *command, char **env)
{
    t_command	*cur_struct;
    t_list		*cur_lst;
    char        *temp;
    int         count;
    int         len;

    len = 0;
    temp = NULL;
    (void)env;
    count = 0;
    cur_struct = command;
    cur_lst = command->args;
    // printf("")
    if (ft_strncmp((const char *)cur_struct->program, "$?", 3) == 0)
        printf("minishell: %d command not found\n", command->not_found);	
    while (cur_struct->args)
    {
        cur_lst = cur_struct->args;
        while (cur_lst)
        {
            if (ft_strncmp((const char *)cur_lst->content, "$", 1) == 0)
            {
                temp = ft_strdup((const char *)cur_lst->content);
                temp++;
                len = ft_strlen(temp);
                count = 0;
                while (env[count])
                {
                    if (ft_strncmp(env[count], temp, len) == 0)
                    {
                        printf("curlist %s\n", cur_lst->content);
                        free(cur_lst->content);
                        cur_lst->content = ft_strdup(env[count]);
                        printf("twee %s\n", cur_lst->content);
                        break ;
                    }
                    count++;
                }
                cur_lst = cur_lst->next;
            }
            cur_lst = cur_struct->args;
        cur_struct->args = cur_struct->args->next;   
        }
    }
    cur_struct = command;
    cur_lst = cur_struct->args;

}