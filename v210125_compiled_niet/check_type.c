/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/01/25 10:37:56 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		remove_next(t_list **list)
{
	(*list)->next = (*list)->next->next;
	//free the lost element?
}


void		voer_uit(t_list **cmd_list, t_list **list, char **env)
{
	//loop door lijst en voer elk cmd uit
	while (cmd_list)
	{
		check_type((*cmd_list)->content, list, env);
		(*cmd_list) = (*cmd_list)->next;
	}
}

t_list		**de_loop(t_list **input)
{
	t_list		**tmp;
	t_list		**cmd_list;
	t_command	*cmd;

	tmp = input;
	while(tmp)
	{
		printf((*tmp)->content);
		if ((char *)((*tmp)->content) == ';')
		{
			cmd = make_command(input);//deze functie maakt eerst cmd leeg
			ft_list_push_back(cmd_list, cmd);
		}
		else if (tmp->content == '|')
		{
			cmd = make_command(input);
			cmd->pipe_left = 1;
		}
		tmp = tmp->next;
	}
	return (cmd_list);
}

/*
t_command	functie(t_list **input)
{
	t_command	cmd;
	t_list		*arglist;

	cmd.program = list->content
	while (list)
	{
		if (ft_strncmp(tmp->content, ";", 1) == 0)
		{
			cmd.args = ft_list_to_array(&arglist);
			printf("eindig struct, stuur door naar uitvoerfunctie\n");
			tmp = tmp-next;
		}
		else if (list->content == '>')
			cmd.output_red = list->next;
		
			cmd.red2 = list->next;
		else if <
			cmd.red3 = list->next;;
		else if |
			cmd.pipe_right = 1;
			list = list->next;
		else
			ft_list_push_back(arglist, &(input->content));
	}
	cmd.args = ft_list_to_array(&arglist);
	return (cmd);
}
*/

/*
t_command	parser(t_list **list)
{
	t_command		cmd;
	t_list			*tmp;

	tmp = *list;
	cmd.program = tmp->content;
	//tmp = tmp->next;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->next->content, ">", 1) == 0)
		{
			remove_next(&tmp);
			//tmp = tmp->next;
			cmd.redirection = ft_strdup(tmp->next->content);
			remove_next(&tmp);
		}
		tmp = tmp->next;
		if (ft_strncmp(tmp->content, ";", 1) == 0)
		{
			printf("einde van dit command\n");
			// maak hier command en return cmd en loop in functie erboven over list?
			parser(tmp->next);//maar nu voer je eerst uit wat na ; komt..
			//roep deze functie opnieuw aan met list->next?
			//tmp->next = NULL;
		}
	}
	tmp = *list;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	tmp = *list;
	cmd.args = ft_list_to_array(&tmp);
	return (cmd);
}
*/

t_command	make_command(t_list **list)
{
	t_command		cmd;

	cmd.program = list[0]->content;//zou kunnen dat dit niet werkt nu **list
	//hier moet nog > >> en < opgevangen worden
	cmd.args = ft_list_to_array(list);
	return (&cmd);
}

void    	check_type(t_command *cmd, t_list **list, char **env)
{//deze krijgt t_command ipv t_list
	t_list	*current;

	//(void)env;
	current = *list;
	while (current)
	{
		if (ft_strncmp((const char *)current->content, "cat", 3) == 0)
			printf("cat type\n");
		if (ft_strncmp((const char *)current->content, "cp", 2) == 0)
			printf("cp type\n");//parser(list);
		if (ft_strncmp((const char *)current->content, "echo", 4) == 0)
			printf("echo type\n");
		current = current->next;
	}
	current = *list;
	external(cmd, env);	
// als geen van de 7 builtins voldoet bij strcmp, stuur door naar de functie 'external'
}
