/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/25/01 11:04:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/12/01 11:55:26 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_command		*ft_create_linked_struct(char *data)
// {
// 	t_command *command;

// 	command = malloc(sizeof(t_command));
// 	if (command)
// 	{
//         command->program = data;
//         command->args = ft_strdup("");
//         command->pipe_left = 0;
//         command->pipe_right = 0;
// 		command->redirection = NULL;
// 		command->next = NULL;
// 	}
// 	return (command);
// }

// void	ft_struct_clear(t_command *command, void (*del)(void*))
// {
// 	t_command *temp;

// 	temp = *lst;
// 	while (temp)
// 	{
// 		temp = (*lst)->next;
// 		del((*lst)->content);
// 		free(*lst);
// 		(*lst) = temp;
// 	}
// 	*lst = NULL;
// }

void error_handler(char *error, t_list **list, t_command *command)
{
    write(1, "minishell: ", 11);
    write(1, error, ft_strlen(error));
    (void)command;
    ft_lstclear(list, free); //checken of dit goed werkt
    // free(t_command)
    exit(0); // of moeten we ook op vork letten?
}