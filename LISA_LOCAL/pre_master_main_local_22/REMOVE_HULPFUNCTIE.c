/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   REMOVE_HULPFUNCTIE.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 12:03:58 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/09 10:55:57 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void			array_printer(char **array)
// {
// 	int			i;

// 	i = 0;
// 	while (args[i])
// 	{
// 		printf("%s\n", args[i]);
// 		i++;
// 	}
// }

// void			print_list(t_list *list)
// {
// 	while (list)
// 	{
// 		printf("[%s]-\n", list->content);
// 		list = list->next;
// 	}
// }


void			print_cur_struct(t_command *command)
{
	t_command *cur_struct;
	t_list 	*cur_args;
	
	cur_struct = command;
	printf("%p\n", command->args);
	// cur_args = cur_struct->args;
	
	while (cur_struct)// loop om te lezen wat er gebeurt, later weghalen
	{
		cur_args = cur_struct->args;
		printf("\n");
		printf("\tprogram: [%s]\n", ((char*)(cur_struct)->program));
		if (!(cur_struct)->in_red)
			printf("\tin_red: [(null)]\n");
		while (((cur_struct)->in_red))
		{
			printf("\tin_red: [%s]\n", ((cur_struct)->in_red)->content);
			(cur_struct)->in_red = (cur_struct)->in_red->next;
		}
		if (!(cur_struct)->out_red)
			printf("\tout_red: [(null)]\n");
		while (((cur_struct)->out_red))
		{
			printf("\tout_red: [%s]\n", ((cur_struct)->out_red)->content);
			(cur_struct)->out_red = (cur_struct)->out_red->next;
		}
		if (!cur_args)
			printf("\targs: [(null)]\n");
		while ((cur_args))
		{
			printf("\targs: [%s]\n", cur_args->content);
			cur_args = cur_args->next;
		}
		printf("\tpipe_left: [%d]\n", ((cur_struct)->pipe_left));
		printf("\tpipe_right: [%d]\n", ((cur_struct)->pipe_right));
		printf("\tfd_in: [%d]\n", ((cur_struct)->fd_in));
		printf("\tfd_out: [%d]\n\n", ((cur_struct)->fd_out));
		cur_struct = (cur_struct)->next;
	}
	cur_struct = command;
	cur_args = cur_struct->args;
	printf("%p\n", command->args);
}
