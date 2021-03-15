/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 11:38:21 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/15 14:53:57 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    expansions(t_command *command, char **env)
{
    t_command	*cur_struct;
    t_list		*cur_lst;

	cur_lst = cur_struct->args->content;
    char        *temp;
    int         count;
    int         len;

    len = 0;
    temp = NULL;
    (void)env;
    count = 0;
	cur_struct = command;
    if (ft_strncmp((const char *)cur_struct->program, "$?", 3) == 0)
        printf("minishell: %d command not found\n", command->not_found);	
    // else if (ft_strncmp((const char *)cur_struct->program, "$", 1) == 0)
    // {
    //     // cur_struct->program++;
    //     temp = ft_strdup((const char *)cur_struct->program);
    //     temp++;
    //     len = ft_strlen(temp);
    //     while (env[count])
    //     {
    //         ft_strncmp(env[count], temp, len) == 0);

    //         count++;
    //     }
       
    //     printf("temp %s\n", temp);
    // }

    while (cur_struct->args)
    {
        if (ft_strncmp((const char *)cur_struct->args->content, "$", 1) == 0)
        {
            printf("ja");
            // cur_struct->program++;
            temp = ft_strdup((const char *)cur_struct->args->content);
            temp++;
            len = ft_strlen(temp);
            printf("strlen: %d", len);
            while (env[count])
            {
                if (ft_strncmp(env[count], temp, len) == 0)
                {
                    printf("ja");
                    // printf("env %s", env[count]);
                    free(cur_struct->args->content);
                    cur_struct->args->content = ft_strdup(env[count]);
                    printf("env %s", cur_struct->args->content);
                }
                count++;
            }
        }
        count = 0;
        cur_struct->args = cur_struct->args->next;
    }
    cur_struct = command;
}