/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 14:03:48 by rde-vrie      #+#    #+#                 */
/*   Updated: 2021/03/01 17:17:57 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//export = laat "declare -x env[i]" zien voor elke i
//export "iets=bla" zet precies dat in de env.
//als je dan env intypt, komt ie erbij te staan.
//als er geen = teken in de argumenten staat: niet in env zetten
//zodra er 1 = teken in voorkomt, precies zoals ingetypt het erin zetten
//meerdere argumenten kan, elk arg heeft een = teken nodig. splits op spaties.
//alleen een = zonder andere dingen is invalid
//param mag niet met getal beginnen, getal mag wel als waarde (na de =)
//param mag wel met _ beginnen

#include "minishell.h"



void	export_func(t_command *command, char **env)
{
	int	i;
	t_list *begin_arg;

	i = 0;
	if (command->args == NULL)
	{
		printf("\tprint alle envs uit\n");
		(void)env;
		return ;
	}
	begin_arg = command->args;
	while (command->args)
	{
		if (ft_isalpha(*(command->args->content)) == 1 || *(command->args->content) == '_') //check of het begin _ of letter is
		{
			printf("\tgoed begin");
			if (ft_strchr(command->args->content, '=') == 0)// als er geen = in zit
			{
				printf("\tgeen =\n");
				break ;
			}
			printf("\tkomt erin\n");
		}
		else
			printf("export: `%s': not a valid identifier\n", command->args->content);
		command->args = command->args->next;
	}
}
