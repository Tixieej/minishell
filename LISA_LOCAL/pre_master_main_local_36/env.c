/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 11:38:21 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/02 12:28:44 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        env_check(t_command *command, char **env)
{
    // = teken af
    (void)command;
    char    *result;
    int     times;
    int     check;
    int     len;

    
    len = 0;
    result = ft_strdup("");
    check = 0;
    times = 0;
    if (command->args)
        len = ft_strlen(command->args->content);
    while (env[times] != '\0')//(*env[times] != '_') //check bij rixt?
    {
        result = ft_strjoin(result, env[times]);
        result = ft_strjoin(result, "\n");
        if (len > 0)
            if (ft_strncmp(env[times], command->args->content, len) != 0)
                check++;
        times++;
    }
    if (check > 0)
    {
        printf("env: %s: No such file or directory", command->args->content);
        return ;
    }
    else
        printf("%s\n", result);
    free(result);
}
