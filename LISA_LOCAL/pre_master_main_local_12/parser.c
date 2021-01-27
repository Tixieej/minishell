/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/12/01 15:55:26 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command		*ft_create_linked_struct(char *data)
{
	t_command *command;

	command = malloc(sizeof(t_command));
	if (command)
	{
        command->program = data;
		command->args = NULL;
        command->pipe_left = 0;
        command->pipe_right = 0;
		command->in_red = NULL;
		command->out_red = NULL;
		command->next = NULL;
	}
	return (command);
}

void		ft_struct_push_back(t_command **begin_list, char *data)
{
	t_command	*temp;
	temp = *begin_list;
	if (*begin_list)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = ft_create_linked_struct(data);
	}
	else
		*begin_list = ft_create_linked_struct(data);
}

void	parser(t_list **list, char **env, t_command	*command)
{
	t_list		*cur_lst;
	t_command	**cur_struct;
	//linked list die de args bijhoudt
	//t_list		*arg_list;

	cur_lst = *list;
	ft_struct_push_back(&command, (char *)cur_lst->content);
	cur_struct = &command;
	cur_lst = cur_lst->next;
	while (cur_lst)
	{
		// if (ft_strncmp((const char *)cur_lst->content, ">", 0))
		// {
		// 	printf("JA\n");
		// }

		/*if (ft_strncmp(<) && ft_strncmp(>) && ft_strncmp(>>) )
		{
			cur_struct

		}*/
		if (ft_strncmp((const char *)cur_lst->content, ";", 1) && ft_strncmp((const char *)cur_lst->content, "|", 1))
		{
			// printf("- het is geen ; of |\n");
			
			
			// if (ft_strchr("<>", (int)cur_lst->content))
			if (!(ft_strncmp((const char *)cur_lst->content, ">", 1)))
			{
				ft_list_push_back(&((*cur_struct)->out_red), cur_lst->content);
				cur_lst = cur_lst->next;
				ft_list_push_back(&((*cur_struct)->out_red), cur_lst->content);
			}
			else if (!(ft_strncmp((const char *)cur_lst->content, "<", 1)))
			{
				ft_list_push_back(&((*cur_struct)->in_red), cur_lst->content);
				cur_lst = cur_lst->next;
				ft_list_push_back(&((*cur_struct)->in_red), cur_lst->content);
			}
			else
				ft_list_push_back(&((*cur_struct)->args), cur_lst->content);
			// Hier binnen kan je dan de dubbele array opbouwen als je zou willen
			//(*cur_struct)->args = ft_strjoin((*cur_struct)->args, cur_lst->content);
		}
		else if (ft_strncmp((const char *)cur_lst->content, ";", 1) == 0)
		{
			// printf("- het is een ;\n");
			check_type(list, env, *cur_struct);
			cur_lst = cur_lst->next;
			ft_struct_push_back(&(*cur_struct), (char *)cur_lst->content);
			cur_struct = &(*cur_struct)->next;
		}	
		else if (ft_strncmp((const char *)cur_lst->content, "|", 1) == 0)
		{
			// printf("- het is een |\n");
			(*cur_struct)->pipe_right = 1;
			cur_lst = cur_lst->next;
			ft_struct_push_back(&(*cur_struct), (char *)cur_lst->content);
			cur_struct = &(*cur_struct)->next;
			(*cur_struct)->pipe_left = 1;
		}
		cur_lst = cur_lst->next;
	}
	check_type(list, env, *cur_struct);
	cur_lst = *list;
	cur_struct = &command;
	// printf("go to execute function\n");
	while (*cur_struct)// loop om te lezen wat er gebeurt, later weghalen
	{
			printf("\tprogram: [%s]\n", ((char*)(*cur_struct)->program));
			while (((*cur_struct)->in_red))
			{
				printf("\tin_red: [%s]\n", ((*cur_struct)->in_red)->content);
				(*cur_struct)->in_red = (*cur_struct)->in_red->next;
			}
			while (((*cur_struct)->out_red))
			{
				printf("\tin_red: [%s]\n", ((*cur_struct)->out_red)->content);
				(*cur_struct)->out_red = (*cur_struct)->out_red->next;
			}
			while (((*cur_struct)->args))
			{
				printf("\targs: [%s]\n", ((*cur_struct)->args)->content);
				(*cur_struct)->args = (*cur_struct)->args->next;
			}
			printf("\tpipe_left: [%d]\n", ((*cur_struct)->pipe_left));
			printf("\tpipe_right: [%d]\n\n", ((*cur_struct)->pipe_right));
			cur_struct = &(*cur_struct)->next;
	}
	cur_struct = &command;
	// ft_lstclear(&cur_lst, free);
	// ft_lstclear(&list, free);  ft_strctclear schrijven
}
