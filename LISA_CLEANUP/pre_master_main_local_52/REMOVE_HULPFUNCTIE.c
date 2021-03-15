/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   REMOVE_HULPFUNCTIE.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/08 12:03:58 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/15 11:01:02 by livlamin      ########   odam.nl         */
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
	t_command	*cur_struct;
	t_list		*cur_args;
	t_list		*cur_in_red;
	t_list		*cur_out_red;
	
	cur_struct = command;
	cur_args = cur_struct->args;
	cur_in_red = cur_struct->in_red;
	cur_out_red = cur_struct->out_red;
	while (cur_struct)// loop om te lezen wat er gebeurt, later weghalen
	{
		cur_args = cur_struct->args;
		cur_in_red = cur_struct->in_red;
		cur_out_red = cur_struct->out_red;
		printf("\n");
		printf("\tprogram: [%s]\n", ((char*)(cur_struct)->program));
		if (!(cur_struct)->in_red)
			printf("\tin_red: [null]\n");
		while (cur_in_red)
		{
			printf("\tin_red: [%s]\n", cur_in_red->content);
			cur_in_red = cur_in_red->next;
		}
		if (!cur_out_red)
			printf("\tout_red: [null]\n");
		while (cur_out_red)
		{
			printf("\tout_red: [%s]\n", cur_out_red->content);
			cur_out_red = cur_out_red->next;
		}
		if (!cur_args)
			printf("\targs: [null]\n");
		while (cur_args)
		{
			printf("\targs: [%s]\n", cur_args->content);
			cur_args = cur_args->next;
		}
		printf("\tpipe_left: [%d]\n", ((cur_struct)->pipe_left));
		printf("\tpipe_right: [%d]\n", ((cur_struct)->pipe_right));
		printf("\tfd_in: [%d]\n", ((cur_struct)->fd_in));
		printf("\tfd_out: [%d]\n\n", ((cur_struct)->fd_out));
		cur_args = cur_struct->args;
		cur_in_red = cur_struct->in_red;
		cur_out_red = cur_struct->out_red;
		cur_struct = (cur_struct)->next;
	}
	cur_struct = command;
}

// void			print_cur_struct(t_command *command)
// {
// 	t_command **cur_struct;
	
// 	cur_struct = &command;
// 	while (*cur_struct)// loop om te lezen wat er gebeurt, later weghalen
// 	{
// 		printf("\n");
// 		printf("\tprogram: [%s]\n", ((char*)(*cur_struct)->program));
// 		if (!(*cur_struct)->in_red)
// 			printf("\tin_red: [(null)]\n");
// 		while (((*cur_struct)->in_red))
// 		{
// 			printf("\tin_red: [%s]\n", ((*cur_struct)->in_red)->content);
// 			(*cur_struct)->in_red = (*cur_struct)->in_red->next;
// 		}
// 		if (!(*cur_struct)->out_red)
// 			printf("\tout_red: [(null)]\n");
// 		while (((*cur_struct)->out_red))
// 		{
// 			printf("\tout_red: [%s]\n", ((*cur_struct)->out_red)->content);
// 			(*cur_struct)->out_red = (*cur_struct)->out_red->next;
// 		}
// 		if (!(*cur_struct)->args)
// 			printf("\targs: [(null)]\n");
// 		while (((*cur_struct)->args))
// 		{
// 			printf("\targs: [%s]\n", ((*cur_struct)->args)->content);
// 			(*cur_struct)->args = (*cur_struct)->args->next;
// 		}
// 		printf("\tpipe_left: [%d]\n", ((*cur_struct)->pipe_left));
// 		printf("\tpipe_right: [%d]\n", ((*cur_struct)->pipe_right));
// 		printf("\tfd_in: [%d]\n", ((*cur_struct)->fd_in));
// 		printf("\tfd_out: [%d]\n\n", ((*cur_struct)->fd_out));
// 		cur_struct = &(*cur_struct)->next;
// 	}
// 	cur_struct = &command;
// }


// static char	**add_env_to_array(char **old_env, char *old_path)
// {
// 	char	**new_env;
// 	int		count;
// 	int		path;
// 	char	*temp;

// 	temp = ft_strdup("OLDPWD=");
// 	count = 0;
// 	path = 0;
// 	while (old_env[count])
// 		count++;
// 	new_env = malloc(sizeof(char *) * count + 2);
// 	if (!new_env)
// 		return (NULL);
// 	new_env[count + 1] = NULL;
// 	while (path < count - 1)
// 	{
// 		new_env[path] = ft_strdup(old_env[path]);
// 		free(old_env[path]);
// 		path++;
// 	}
// 	new_env[path] = ft_strdup(temp);
// 	free(temp);
// 	new_env[path] = ft_strjoin(new_env[path], old_path);
// 	free(old_env[path]);
// 	// free(temp);
// 	return (new_env);
// }