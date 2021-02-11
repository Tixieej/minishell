/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 13:12:48 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/03 14:42:37 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        cd(t_command *command)
{
    char *path;
    int check;

    path = getcwd(NULL, 0);
    // if ((char *)command->args->content == '.')
    

    check = chdir("/Users/lisavlamings/Documents/INLEVEREN_CODAM/MINISHELL/minishell_02/LISA_LOCAL/pre_master_main_local_16/testmap");
    if (check < 0)
        error_handler("path non-existing", NULL, NULL); //veranderen met geheugen
//     printf("%s\n", path);
   printf("args2[%s]\n", (char *)command->args->content);
   	// /* dit is een check en kan later weg */
	// // printf("check_type\n");
	// t_list *begin = command->args;
	// while ((command->args))
	// {
	// 	printf("\targs: [%s]\n", (command->args)->content);
	// 	command->args = command->args->next;
	// }
	// command->args = begin;
	// /* einde check */
}