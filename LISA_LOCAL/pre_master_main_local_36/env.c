/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 11:38:21 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/01 14:47:05 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        env_check(t_command *command, char **env)
{
    printf("ha");
    (void)command;
    (void)env;
    // int times;
    // int check;

    // check = 0;
    // times = 0;
    // if (command->args->content != NULL)
    // {
    //     while (*env[times] != '_')
    //     {
    //         if (ft_strncmp(env[times], command->args->content, ft_strlen(command->args->content)) != 0)
    //             check++;
    //         times++;
    //         printf("ha");
    //     }
    //     if (check > 0)
    //     {
    //         printf("env: %s: No such file or directory", command->args->content);
    //         return ;
    //     }
    //     times = 0;
    // }
    // while (*env[times] != '_') //check bij rixt?
    // {
    //     printf("%s\n", env[times]);
    //     times++;
    // }
}
