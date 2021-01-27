/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/21/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/21/01 15:55:26 by livlamin          ########   odam.nl     */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


    // t_list			*in_red; // <
	// t_list			*out_red; // >> >
// modes : O_RDONLY, O_WRONLY, or O_RDWR.
void        echo(t_command *command)
{
    int fd;
    char *s;

    fd = 0;
    s = ft_strdup("");
    while (command->args)
    {
        s = ft_strjoin(s, (const char *)command->args->content);
        s = ft_strjoin(s, " ");
        command->args = command->args->next;
    }
    //spatie er uit
    s = ft_strjoin(s, "\n"); //dit werkt niet meer, want command->args = linked list nu
    while (command->out_red)
    {
        if (!(ft_strchr(">", (int)command->out_red->content)))
            command->out_red = command->out_red->next;
        printf("%s\n", (const char *)command->out_red->content);
        if (command->out_red)
            fd = open((const char *)command->out_red->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
        command->out_red = command->out_red->next;
    }
	// (void)command;
    // if file doesnt exist && TRUNC
    // fd = open("test", O_CREAT | O_RDWR | O_TRUNC, 0644);
    // fd = open("test", O_CREAT | O_RDWR | O_APPEND, 0644);

    if (write(fd, s, ft_strlen(s)) < 0)
       printf("error\n");
    // if (write(fd, command->args, ft_strlen(command->args)) < 0)
    //     printf("error\n");
    // printf("%s\n", command->args);
    // printf("echo\n");
}