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
        command->args = ft_strdup("");
        command->pipe_left = 0;
        command->pipe_right = 0;
		command->redirection = 0;
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

static void	parser(t_list **list, char **env)
{
	t_command	*command;
	t_list		*cur_lst;
	t_command	**cur_sturct;

	command = NULL;
	cur_sturct = &command;
	cur_lst = *list;

	(void)env;
	ft_struct_push_back(&(*cur_sturct), (char *)cur_lst->content);
	// printf("cur_lst content: [%s]\n", ((char *)cur_lst->content));
	cur_lst = cur_lst->next;
	while (cur_lst)
	{
		if (ft_strncmp((const char *)cur_lst->content, ";", 1) && ft_strncmp((const char *)cur_lst->content, "|", 1))
		{
			(*cur_sturct)->args = ft_strjoin((*cur_sturct)->args, cur_lst->content);
			(*cur_sturct)->args = ft_strjoin((*cur_sturct)->args, " "); //tijdelijk om woorden iig los te lezen
		}
		if (ft_strncmp((const char *)cur_lst->content, ";", 1) == 0)
			printf("go to execute function\n");
		if (ft_strncmp((const char *)cur_lst->content, "|", 1) == 0)
		{
			(*cur_sturct)->pipe_right = 1;
			cur_lst = cur_lst->next;
			ft_struct_push_back(&(*cur_sturct), (char *)cur_lst->content);
			cur_sturct = &(*cur_sturct)->next;
			(*cur_sturct)->pipe_left = 1;
		}
		cur_lst = cur_lst->next;
	}
	cur_lst = *list;
	cur_sturct = &command;
	while (*cur_sturct)// loop om te lezen wat er gebeurd later weghalen
	{
			printf("program: [%s]\n", ((char*)(*cur_sturct)->program));
			printf("args: [%s]\n", ((char*)(*cur_sturct)->args));
			printf("pipe_left: [%d]\n", ((*cur_sturct)->pipe_left));
			printf("pipe_right: [%d]\n", ((*cur_sturct)->pipe_right));
			printf("redirection: [%d]\n", ((*cur_sturct)->redirection));
			// printf("begin adress: %p\n", begin);
			cur_sturct = &(*cur_sturct)->next;
	}
	
}

void    check_type(t_list **list, char **env)
{
	parser(list, env);

	// t_list	*begin;

	// begin = *list;
	// while (begin)
	// {
	// 	if (ft_strncmp((const char *)begin->content, "cat", 3) == 0)
	// 		printf("cat type\n");
	// 	if (ft_strncmp((const char *)begin->content, "cp", 2) == 0)
	// 		non_buildin(*list, env);
	// 	if (ft_strncmp((const char *)begin->content, "echo", 4) == 0)
	// 		printf("echo type\n");
	// 	begin = begin->next;
	// }
	// begin = *list;
}




// void	error(char *str, int ret)
// {
// 	printf("%s\n", str);
// 	if (ret < 0)
// 		exit(-1);
// }

// void    check_type(t_list **list, char **env)
// {
// 	t_list	*begin;

// 	begin = *list;
// 	while (begin)
// 	{
// 		if (ft_strncmp((const char *)begin->content, "echo", 4) == 0)
// 			printf("cat type\n");
// 		if (ft_strncmp((const char *)begin->content, "cd", 2) == 0)
// 			printf("cd type\n");
// 		if (ft_strncmp((const char *)begin->content, "pwd", 3) == 0)
// 			printf("pwd type\n");
// 		if (ft_strncmp((const char *)begin->content, "export", 6) == 0)
// 			printf("export type\n");
// 		if (ft_strncmp((const char *)begin->content, "unset", 5) == 0)
// 			printf("unset type\n");
// 		if (ft_strncmp((const char *)begin->content, "env", 3) == 0)
// 			printf("env type\n");
// 		if (ft_strncmp((const char *)begin->content, "exit", 4) == 0)
// 			printf("exit type\n");
// 		else
// 			non_buildin(*list, env, begin);
// 		// if (ft_parse = -1)
// 		// 	error("invalid programme input", -1);
// 		begin = begin->next;
// 	}
// 	begin = *list;
// }