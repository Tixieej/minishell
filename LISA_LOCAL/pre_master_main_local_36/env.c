/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 11:38:21 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/02 15:29:35 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        env_check(t_command *command, char **env, int len, int times)
{
    char    *result;
    int     check;

    check = 0;
    result = ft_strdup("");
    if (command->args)
        len = ft_strlen(command->args->content);
    while (*env[times] != '_' && *env[times] != '\0') //'_' weg?
    {
        result = ft_strjoin(result, env[times]);
        result = ft_strjoin(result, "\n");
        if (len > 0)
        {
            if (ft_strncmp(env[times], command->args->content, len) == 0)
            {
                if (command->args->content[len - 1] == '=')
                    check++;
            }
        }
        times++;
    }
    if (env[times]) //klopt dit??
        result = ft_strjoin(result, env[times]);
    if (check == 1 || (check == 0 && len == 0))
        printf("%s\n", result);
    else
        printf("env: %s: No such file or directory", (char *)command->args->content);      
    free(result);
    result = NULL;
    return ;
}
