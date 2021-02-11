/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/21 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/08 13:04:41 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// modes : O_RDONLY, O_WRONLY, or O_RDWR.
void        echo(t_command *command)
{
    char *s;
    t_list	*args;

    args = command->args;
    s = ft_strdup("");
	printf("wtf???\n");
    while (args)
    {
		printf("\t--> %s\n", (char *)args->content);
        s = ft_strjoin(s, (const char *)args->content);
        s = ft_strjoin(s, " ");
        args = args->next;
    }
    if (ft_strlen(s) == 0)
        s = ft_strdup("\n");
    else
        s[ft_strlen(s) - 1] = '\n';
    if (write(command->fd_out, s, ft_strlen(s)) < 0)
        printf("error\n");
    free(s);
    s = NULL;
    return;
}
